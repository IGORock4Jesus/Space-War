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

		public MainForm()
		{
			InitializeComponent();
		}

		private void Form1_Load(object sender, EventArgs e)
		{
			renderer = new Renderer(this);
			renderer.Drawing += Renderer_Drawing;

			ecs = new ECS.Manager();
			ecs.AddSystem(new TransformSystem());
			ecs.AddSystem(new UI.SpriteSystem(this));
			ecs.AddSystem(new UI.MouseZoneSystem(this));
			ecs.AddSystem(new UI.CollisionSystem());
			ecs.AddSystem(new UI.ButtonSystem());
			ecs.AddSystem(new UI.LabelSystem(renderer));

			scene = new ECS.Scene();

			isRunning = true;
			task = new Thread(StartAll);
			renderTask = new Thread(StartRendering);

			task.Start();
			renderTask.Start();

			uiManager = new UI.Manager(ecs, scene);

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
			const int mx = 100, my = 100;
			int mw = ClientSize.Width / mx, mh = ClientSize.Height / my;

			for (int x = 0; x < mx; x++)
			{
				for (int y = 0; y < my; y++)
				{
					string text = $"Button_{x * my + y}";
					var button = uiManager.CreateButton(new SharpDX.Vector2(x * mw, y * mh),
						new SharpDX.Size2F(mw, mh), text);
					button.Get<MouseZone>().Down += MainForm_Down;
					button.Name = text;
					scene.Add(button);
				}

			}
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

			}
		}

		private void Renderer_Drawing(SharpDX.Direct3D9.Device device)
		{
			ecs.Render(renderer);
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
