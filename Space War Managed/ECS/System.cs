using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Space_War_Managed.ECS
{
	class System
	{
		internal virtual void Render(Renderer renderer) { }
		internal virtual void Update(float time) { }
	}

	class System<T> : System where T : Component, new()
	{
		protected List<T> Components { get; } = new List<T>();

		public virtual T Create(Entity entity)
		{
			T t = new T();
			t.Initialize(entity);
			Components.Add(t);
			return t;
		}
	}
}
