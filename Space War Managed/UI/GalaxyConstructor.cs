using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Space_War_Managed.ECS;

namespace Space_War_Managed.UI
{
	class GalaxyConstructor : ECS.Component
	{
		protected override void OnInitialize(Entity entity)
		{
			var mouseZone = entity.Get<MouseZone>();
			mouseZone.Down += MouseZone_Down;
		}

		private void MouseZone_Down(Entity entity, SharpDX.Vector2 point)
		{
		}
	}

	class GalaxyConstructorSystem : ECS.System<GalaxyConstructor>
	{

	}
}
