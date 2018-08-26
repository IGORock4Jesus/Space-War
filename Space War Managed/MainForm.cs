using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Space_War_Managed
{
	public partial class MainForm : Form
	{
		Renderer renderer;
		ECS.Manager ecs;
		private bool isRunning;
		private Task task;
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
			ecs.AddSystem(new UI.SpriteSystem(this));

			scene = new ECS.Scene();

			isRunning = true;
			task = Task.Run(new Action(StartAll));

			Test();
		}

		private void Test()
		{
			ECS.Entity entity = new ECS.Entity();

			var sprite = ecs.Get<UI.SpriteSystem>().Create(entity);

			sprite.Position = new SharpDX.Vector2(20, 20);
			sprite.Size = new SharpDX.Vector2(100, 100);
			sprite.Color = 0xffff0000;

			scene.Add(entity);
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

				renderer.Rendering();
			}
		}

		private void Renderer_Drawing(SharpDX.Direct3D9.Device device)
		{
			ecs.Render(renderer);
		}

		private void Form1_FormClosed(object sender, FormClosedEventArgs e)
		{
			isRunning = false;
			task.Wait();

			renderer.Dispose();
		}
	}
}
