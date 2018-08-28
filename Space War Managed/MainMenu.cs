using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Space_War_Managed.ECS;

namespace Space_War_Managed
{
	class MainMenu : GameStackItem
	{
		ECS.Entity constructorButton;

		public override void Initialize()
		{
			InitializeControls();
		}
		public override void Release()
		{
			ReleaseControls();
		}
		public override void Suspend()
		{
			ReleaseControls();
		}
		public override void Resume()
		{
			InitializeControls();
		}

		private void InitializeControls()
		{
			constructorButton = UI.CreateButton(new SharpDX.Vector2(10, 10), new SharpDX.Size2F(100, 30), "Конструктор");
			constructorButton.Get<UI.Button>().Click += ConstructorButton_Click;
			Scene.Add(constructorButton);
		}

		private void ReleaseControls()
		{
			Scene.Remove(constructorButton);
		}

		private void ConstructorButton_Click(Entity entity)
		{
			// открываем конструктор галактики
			GameStack.Push(new GalaxyConstructor());
		}
	}
}
