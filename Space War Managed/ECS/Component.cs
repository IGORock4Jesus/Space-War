using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed.ECS
{
	class Component
	{
		public Entity Entity { get; private set; }

		protected virtual void OnInitialize(Entity entity) { }

		public void Initialize(Entity entity)
		{
			Entity = entity;
			OnInitialize(entity);
		}
	}
}
