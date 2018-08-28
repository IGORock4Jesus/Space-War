using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Space_War_Managed
{
	class Input
	{
		private MainForm mainForm;

		public Input(MainForm mainForm)
		{
			this.mainForm = mainForm;
			mainForm.KeyDown += MainForm_KeyDown;
			mainForm.KeyUp += MainForm_KeyUp;
			mainForm.KeyPress += MainForm_KeyPress;

			mainForm.MouseDown += MainForm_MouseDown;
			mainForm.MouseMove += MainForm_MouseMove;
			mainForm.MouseUp += MainForm_MouseUp;
			mainForm.MouseWheel += MainForm_MouseWheel;
		}

		private void MainForm_MouseWheel(object sender, MouseEventArgs e)
		{
			MouseWheel?.Invoke(MakeMouse(e));
		}

		private void MainForm_MouseUp(object sender, MouseEventArgs e)
		{
			MouseUp?.Invoke(MakeMouse(e));
		}

		private void MainForm_MouseMove(object sender, MouseEventArgs e)
		{
			MouseMove?.Invoke(MakeMouse(e));
		}

		private void MainForm_MouseDown(object sender, MouseEventArgs e)
		{
			MouseDown?.Invoke(MakeMouse(e));
		}

		private Mouse MakeMouse(MouseEventArgs e)
		{
			return new Mouse
			{
				Buttons = e.Button,
				Cursor = e.Location,
				Wheel = e.Delta / SystemInformation.MouseWheelScrollDelta
			};
		}

		private void MainForm_KeyUp(object sender, KeyEventArgs e)
		{
			KeyUp?.Invoke(e.KeyCode);
		}

		private void MainForm_KeyDown(object sender, System.Windows.Forms.KeyEventArgs e)
		{
			KeyDown?.Invoke(e.KeyCode);
		}

		private void MainForm_KeyPress(object sender, KeyPressEventArgs e)
		{
			//KeyPress?.Invoke(e.)
		}

		public delegate void KeyboardHandler(Keys key);
		public event KeyboardHandler KeyDown, KeyUp, KeyPress;

		public class Mouse
		{
			public Point Cursor { get; set; }
			public MouseButtons Buttons { get; set; }
			public int Wheel { get; set; }
		}
		public delegate void MouseHandler(Mouse mouse);
		public event MouseHandler MouseDown, MouseUp, MouseMove, MouseWheel;
	}
}
