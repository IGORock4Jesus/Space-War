using SharpDX;
using SharpDX.Direct3D9;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed
{
	class Renderer : IDisposable
	{
		Direct3D direct;
		Device device;

		public delegate void DrawHandler(Device device);
		public event DrawHandler Drawing;
		public Device Device => device;


		public Renderer(MainForm form)
		{
			direct = new Direct3D();

			device = new Device(direct, 0, DeviceType.Hardware, form.Handle, CreateFlags.HardwareVertexProcessing, new PresentParameters
			{
				BackBufferCount = 1,
				BackBufferFormat = Format.X8R8G8B8,
				BackBufferHeight = form.ClientSize.Height,
				BackBufferWidth = form.ClientSize.Width,
				DeviceWindowHandle = form.Handle,
				SwapEffect = SwapEffect.Discard,
				Windowed = true
			});

			device.SetRenderState(RenderState.Lighting, false);
		}

		public void Rendering()
		{
			device.Clear(ClearFlags.Target, Color.Gray, 1.0f, 0);
			device.BeginScene();

			Drawing?.Invoke(device);

			device.EndScene();
			device.Present();
		}

		public void Dispose()
		{
			if (device != null)
				device.Dispose();
			if (direct != null)
				direct.Dispose();
		}
	}
}
