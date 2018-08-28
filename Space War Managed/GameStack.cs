using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed
{
	class GameStackItem
	{
		public virtual void Initialize() { }
		public virtual void Release() { }
		public virtual void Suspend() { }
		public virtual void Resume() { }
		public virtual void Update(float time) { }
		public virtual void Render(Renderer renderer) { }

		public ECS.Scene Scene { get; private set; }
		public ECS.Manager ECS { get; private set; }
		public UI.Manager UI { get; private set; }
		public GameStack GameStack { get; private set; }
		public Input Input { get; private set; }
		public MainForm MainForm { get; private set; }

		internal void Initialize(ECS.Scene scene, ECS.Manager ecsManager, UI.Manager uiManager, GameStack gameStack, Input input, MainForm mainForm)
		{
			Scene = scene; ECS = ecsManager; UI = uiManager; GameStack = gameStack;Input = input; MainForm = mainForm;
		}
	}

	class GameStack
	{
		readonly Stack<GameStackItem> items = new Stack<GameStackItem>();
		readonly object locker = new object();
		readonly Queue<GameStackItem> adding = new Queue<GameStackItem>();
		private readonly ECS.Scene scene;
		private readonly ECS.Manager ecsManager;
		private readonly UI.Manager uiManager;
		readonly Input input;
		private readonly MainForm mainForm;
		int popCount = 0;

		public GameStack(ECS.Scene scene, ECS.Manager ecsManager, UI.Manager uiManager, Input input, MainForm mainForm)
		{
			this.scene = scene;
			this.ecsManager = ecsManager;
			this.uiManager = uiManager;
			this.input = input;
			this.mainForm = mainForm;
		}

		public void Push(GameStackItem item)
		{
			item.Initialize(scene, ecsManager, uiManager, this, input, mainForm);

			adding.Enqueue(item);
		}

		public void Pop()
		{
			popCount++;
		}

		public void Update(float time)
		{
			lock (locker)
			{
				if (popCount != 0)
				{
					popCount--;
					if (items.Count != 0)
					{
						var peek = items.Pop();
						peek.Release();

						if (items.Count != 0)
						{
							peek = items.Peek();
							peek.Resume();
						}
					}
				}
				else if (adding.Count != 0)
				{
					if (items.Count != 0)
					{
						var peek = items.Peek();
						peek.Suspend();
					}

					var add = adding.Dequeue();
					add.Initialize();

					items.Push(add);
				}
				else
				{
					foreach (var item in items)
					{
						item.Update(time);
					}
				}
			}
		}

		public void Render(Renderer renderer)
		{
			lock (locker)
			{
				foreach (var item in items)
				{
					item.Render(renderer);
				}
			}
		}
	}
}
