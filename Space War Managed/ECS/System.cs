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
		List<T> components = new List<T>();
		object locker = new object();

		protected T[] Components { get { lock (locker) return components.ToArray(); } }
		//protected List<T> Components { get { lock (components) return components.ToList(); } }

		public virtual T Create(Entity entity, params object[] ps)
		{
			T t = new T();
			Add(entity, t);
			if (ps.Length != 0)
				t.InitialArguments(ps);
			return t;
		}

		public virtual void Add(Entity entity, T component)
		{
			component.Initialize(entity);
			lock (locker) components.Add(component);
			entity.Add(component);
			component.Releasing += Component_Releasing;
		}

		private void Component_Releasing(Component sender)
		{
			Remove(sender);
		}

		public void Remove(Component component)
		{
			lock (locker)
			{
				components.Remove(component as T);
			}
		}
	}
}
