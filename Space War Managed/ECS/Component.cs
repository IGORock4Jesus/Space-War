using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed.ECS
{
	class Component
	{
		public delegate void ComponentHandler(Component sender);
		public event ComponentHandler Releasing;

		public Entity Entity { get; private set; }

		protected virtual void OnInitialize(Entity entity) { }
		protected virtual void OnInitialArguments(params object[] ps) { }

		public void Initialize(Entity entity)
		{
			Entity = entity;
			OnInitialize(entity);
		}

		internal void InitialArguments(params object[] ps)
		{
			OnInitialArguments(ps);
		}

		internal void Release()
		{
			Releasing?.Invoke(this);
		}
	}
}
