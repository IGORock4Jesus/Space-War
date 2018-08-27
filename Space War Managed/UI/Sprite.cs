using SharpDX;
using Space_War_Managed.ECS;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed.UI
{
	class Sprite : ECS.Component
	{
		private Transform transform;

		public Transform Transform => transform;
		public Size2F Size { get; set; }
		public SharpDX.Color Color { get; set; }

		protected override void OnInitialize(Entity entity)
		{
			transform = entity.Get<Transform>();
		}
	}

	class SpriteSystem : ECS.System<Sprite>
	{
		struct Vertex
		{
			public Vector4 pos;
			public uint color;
		}

		private Size clientSize;

		public SpriteSystem(MainForm form)
		{
			clientSize = form.ClientSize;
			form.SizeChanged += Form_SizeChanged;
		}

		private void Form_SizeChanged(object sender, EventArgs e)
		{
			clientSize = (sender as MainForm).ClientSize;
		}

		internal override void Render(Renderer renderer)
		{
			var device = renderer.Device;
			device.SetTransform(SharpDX.Direct3D9.TransformState.View, Matrix.LookAtRH(new Vector3(0, 0, -10), new Vector3(0, 0, 0), new Vector3(0, -1, 0)));
			device.SetTransform(SharpDX.Direct3D9.TransformState.Projection, Matrix.OrthoOffCenterRH(-clientSize.Width / 2.0f, clientSize.Width / 2.0f, -clientSize.Height / 2.0f, clientSize.Height / 2.0f, 0.1f, 1000.0f));

			device.VertexFormat = SharpDX.Direct3D9.VertexFormat.PositionRhw | SharpDX.Direct3D9.VertexFormat.Diffuse;

			var cs = Components;
			foreach (var c in cs)
			{
				var pos = c.Transform.Postion;
				var color = c.Color.ToArgb();

				device.DrawUserPrimitives(SharpDX.Direct3D9.PrimitiveType.TriangleFan, 2, new Vertex[]
				{
					new Vertex {
						pos = new Vector4(pos, 0.0f, 1.0f),
						color = color
					},
					new Vertex {
						pos = new Vector4(pos + new Vector2(c.Size.Width, 0.0f), 0.0f, 1.0f),
						color = color
					},
					new Vertex {
						pos = new Vector4(pos.X + c.Size.Width, pos.Y + c.Size.Height, 0.0f, 1.0f),
						color = color
					},
					new Vertex {
						pos = new Vector4(pos + new Vector2(0.0f, c.Size.Height), 0.0f, 1.0f),
						color = color
					},
				});
			}
		}
	}
}
