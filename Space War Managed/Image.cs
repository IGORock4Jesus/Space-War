using SharpDX;
using SharpDX.Direct3D9;
using Space_War_Managed.ECS;
using Space_War_Managed.Graphics;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed
{
	class Image : Component
	{
		public Transform Transform { get; private set; }
		public Size2F Size { get; set; } = new Size2F(10, 10);
		public Graphics.Texture Texture { get; set; }

		protected override void OnInitialize(Entity entity)
		{
			Transform = entity.Get<Transform>();
		}
	}

	class ImageSystem : System<Image>
	{
		struct Vertex
		{
			public Vector4 pos;
			public Vector2 texel;
		}

		private Size clientSize;
		private readonly Renderer renderer;

		public ImageSystem(MainForm form, Renderer renderer)
		{
			clientSize = form.ClientSize;
			form.SizeChanged += Form_SizeChanged;
			this.renderer = renderer;
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

			device.VertexFormat = SharpDX.Direct3D9.VertexFormat.PositionRhw | SharpDX.Direct3D9.VertexFormat.Texture1;

			device.SetRenderState(SharpDX.Direct3D9.RenderState.AlphaBlendEnable, true);
			device.SetRenderState(SharpDX.Direct3D9.RenderState.SourceBlend, Blend.SourceAlpha);
			device.SetRenderState(RenderState.DestinationBlend, Blend.InverseSourceAlpha);

			var cs = Components;
			foreach (var c in cs)
			{
				var pos = c.Transform.Postion;
				c.Texture?.SetToDevice(device);

				device.DrawUserPrimitives(SharpDX.Direct3D9.PrimitiveType.TriangleFan, 2, new Vertex[]
				{
					new Vertex {
						pos = new Vector4(pos, 0.0f, 1.0f),
						texel = new Vector2(0.0f, 0.0f)
					},
					new Vertex {
						pos = new Vector4(pos + new Vector2(c.Size.Width, 0.0f), 0.0f, 1.0f),
						texel = new Vector2(1.0f, 0.0f)
					},
					new Vertex {
						pos = new Vector4(pos.X + c.Size.Width, pos.Y + c.Size.Height, 0.0f, 1.0f),
						texel = new Vector2(1.0f, 1.0f)
					},
					new Vertex {
						pos = new Vector4(pos + new Vector2(0.0f, c.Size.Height), 0.0f, 1.0f),
						texel = new Vector2(0.0f, 1.0f)
					},
				});
			}

			device.SetRenderState(SharpDX.Direct3D9.RenderState.AlphaBlendEnable, false);
		}

		internal Graphics.Texture LoadFile(string filename)
		{
			return new Graphics.Texture(renderer, filename);
		}
	}
}
