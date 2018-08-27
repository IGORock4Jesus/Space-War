using SharpDX;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed
{
	static class ColorEx
	{
		public static uint ToArgb(this Color _this)
		{
			return	(uint)(_this.A << 24) +
					(uint)(_this.R << 16) +
					(uint)(_this.G << 8) +
					(uint)(_this.B);
		}
	}
}
