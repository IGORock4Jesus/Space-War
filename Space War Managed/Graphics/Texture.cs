using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using SharpDX.Direct3D9;

namespace Space_War_Managed.Graphics
{
	class Texture : IDisposable
	{
		SharpDX.Direct3D9.Texture d3dTexture;
		private readonly string filename;

		public Texture(Renderer renderer, string filename)
		{
			renderer.BeforeReset += Renderer_BeforeReset;
			renderer.AfterReset += Renderer_AfterReset;
			this.filename = filename;

			Load(renderer.Device);
		}

		public void SetToDevice(Device device, int index = 0)
		{
			device.SetTexture(index, d3dTexture);
		}

		private void Load(Device device)
		{
			d3dTexture = SharpDX.Direct3D9.Texture.FromFile(device, filename);
		}

		private void Renderer_AfterReset(Device device)
		{
			Release();
			Load(device);
		}

		private void Renderer_BeforeReset(Device device)
		{
			Release();
		}

		public void Dispose()
		{
			Release();
		}

		private void Release()
		{
			if(d3dTexture != null)
			{
				d3dTexture.Dispose();
				d3dTexture = null;
			}
		}
	}
}
