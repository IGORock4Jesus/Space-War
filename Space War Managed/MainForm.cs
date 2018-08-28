using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using Space_War_Managed.UI;

namespace Space_War_Managed
{
	public partial class MainForm : Form
	{
		Renderer renderer;
		ECS.Manager ecs;
		private bool isRunning;
		private Thread task;
		private Thread renderTask;
		private Manager uiManager;
		private ECS.Scene scene;
		GameStack gameStack;
		Input input;

		public MainForm()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			input = new Input(this);

			renderer = new Renderer(this);
			renderer.Drawing += Renderer_Drawing;

			ecs = new ECS.Manager();
			ecs.AddSystem(new TransformSystem());
			ecs.AddSystem(new UI.SpriteSystem(this));
			ecs.AddSystem(new UI.MouseZoneSystem(input));
			ecs.AddSystem(new UI.CollisionSystem());
			ecs.AddSystem(new UI.ButtonSystem());
			ecs.AddSystem(new UI.LabelSystem(renderer));
			ecs.AddSystem(new UI.GalaxyConstructorSystem());
			ecs.AddSystem(new ImageSystem(this, renderer));

			scene = new ECS.Scene();

			isRunning = true;
			task = new Thread(StartAll);
			renderTask = new Thread(StartRendering);

			uiManager = new UI.Manager(ecs, scene);
			gameStack = new GameStack(scene, ecs, uiManager, input, this);

			task.Start();
			renderTask.Start();

			Test();
		}

		private void StartRendering()
		{
			while (isRunning)
			{
				renderer.Rendering();
				Thread.Sleep(1);
			}
		}

		private void Test()
		{
			gameStack.Push(new MainMenu());
		}

		private void MainForm_Down(ECS.Entity entity, SharpDX.Vector2 point)
		{
			MessageBox.Show($@"Mouse button down => {entity.Name} ({point})");
		}

		private void StartAll()
		{
			int oldTime = Environment.TickCount;
			while (isRunning)
			{
				int newTime = Environment.TickCount;
				float time = (newTime - oldTime) * 0.001f;
				oldTime = newTime;

				ecs.Update(time);
				gameStack.Update(time);
			}
		}

		private void Renderer_Drawing(SharpDX.Direct3D9.Device device)
		{
			ecs.Render(renderer);
			gameStack.Render(renderer);
		}

		private void Form1_FormClosed(object sender, FormClosedEventArgs e)
		{
			isRunning = false;
			renderTask.Join();
			renderer.Dispose();
			//task.Wait();
		}
	}
}
