using SharpDX;
using SharpDX.Direct3D9;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace Space_War_Managed
{
	class Renderer : IDisposable
	{
		Direct3D direct;
		Device device;
		bool canDraw;
		private bool inDrawing;

		public delegate void DrawHandler(Device device);
		public event DrawHandler Drawing;
		public Device Device => device;


		public Renderer(MainForm form)
		{
			direct = new Direct3D();

			device = new Device(direct, 0, DeviceType.Hardware, form.Handle, CreateFlags.HardwareVertexProcessing, new PresentParameters
			{
				BackBufferFormat = Format.X8R8G8B8,
				BackBufferHeight = form.ClientSize.Height,
				BackBufferWidth = form.ClientSize.Width,
				DeviceWindowHandle = form.Handle,
				SwapEffect = SwapEffect.Discard,
				Windowed = true
			});

			device.SetRenderState(RenderState.Lighting, false);

			form.SizeChanged += Form_SizeChanged;

			canDraw = true;
		}

		private void Form_SizeChanged(object sender, EventArgs e)
		{
			if (!(sender is MainForm mainForm)) return;

			var size = mainForm.ClientSize;

			OnPreReset();

			device.Reset(new PresentParameters
			{
				BackBufferFormat = Format.X8R8G8B8,
				BackBufferHeight = size.Height,
				BackBufferWidth = size.Width,
				DeviceWindowHandle = mainForm.Handle,
				SwapEffect = SwapEffect.Discard,
				Windowed = true
			});

			OnPostReset();
		}

		private void OnPostReset()
		{
			canDraw = true;
		}

		private void OnPreReset()
		{
			canDraw = false;
			while (inDrawing)
			{
				Thread.Sleep(1);
			}
		}

		public void Rendering()
		{
			if (!canDraw) return;

			inDrawing = true;

			try
			{
				device.Clear(ClearFlags.Target, Color.Gray, 1.0f, 0);
				device.BeginScene();

				Drawing?.Invoke(device);

				device.EndScene();
				device.Present();
			}
			catch(Exception ex)
			{
				Debug.WriteLine(ex);
				// ждем 1 сек
				Thread.Sleep(1000);
			}

			inDrawing = false;
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
