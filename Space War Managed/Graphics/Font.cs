using SharpDX;
using SharpDX.Direct3D9;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed.Graphics
{
	class Font : IDisposable
	{
		SharpDX.Direct3D9.Font d3dFont;
		private readonly FontDescription description;

		public Font(Renderer renderer, FontDescription description)
		{
			renderer.BeforeReset += Renderer_BeforeReset;
			renderer.AfterReset += Renderer_AfterReset;

			d3dFont = new SharpDX.Direct3D9.Font(renderer.Device, description);
			this.description = description;
		}

		private void Renderer_AfterReset(Device device)
		{
			Release();
			d3dFont = new SharpDX.Direct3D9.Font(device, description);
		}

		private void Renderer_BeforeReset(Device device)
		{
			Release();
		}

		private void Release()
		{
			if (d3dFont != null)
			{
				d3dFont.Dispose();
				d3dFont = null;
			}
		}

		public void Dispose()
		{
			Release();
		}

		internal void DrawText(string text, Rectangle rectangle, FontDrawFlags fontDrawFlags, Color color)
		{
			d3dFont?.DrawText(null, text, rectangle, fontDrawFlags, color);
		}
	}
}
