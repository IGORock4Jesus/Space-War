#pragma once
#include <typeinfo>
#include <string>
#include <d3dx9.h>

namespace ECS
{
	constexpr size_t MAX_COMPONENTS = 100000;
	constexpr size_t MAX_ENTITY_COMPONENTS = 8;

	class Entity;

	template <typename T>
	size_t GetTypeHash() {
		static const size_t hash = typeid(T).hash_code();
		return hash;
	}

	class ComponentBase {
	public:
		const size_t hashType;
		ComponentBase(size_t hashType)
			: hashType{ hashType } {}

		virtual ~ComponentBase() {}

		virtual void OnInitialize(Entity* entity) {}
	};

	template <typename T>
	class Component : public ComponentBase {
		//static_assert(std::is_base_of<ComponentBase, T>::value, "TComponent должен наследовать ECS::Component!");
	public:
		Component() 
			: ComponentBase(GetTypeHash<T>())
		{}
	};

	class Entity {
		std::string name;
		ComponentBase* components[MAX_ENTITY_COMPONENTS];

	public:
		Entity() {
			memset(components, 0, sizeof(ComponentBase*) * MAX_ENTITY_COMPONENTS);
		}

		void SetName(std::string name) { this->name = name; }
		const std::string GetName() const { return name; }

		template <typename T>
		void AddComponent(T* c) {
			static_assert(std::is_base_of<ComponentBase, T>::value, "T должен наследовать ECS::Component!");

			for (size_t i = 0; i < MAX_ENTITY_COMPONENTS; i++)
			{
				if (!components[i]) {
					components[i] = c;
					return;
				}
			}

			throw std::overflow_error("Объект не может содержать больше компонентов.");
		}

		template <typename T>
		T* GetComponent() {
			static_assert(std::is_base_of<ComponentBase, T>::value, "T должен наследовать ECS::Component!");

			auto tHash = typeid(T).hash_code();

			for (size_t i = 0; i < MAX_ENTITY_COMPONENTS; i++)
			{
				if (components[i] && components[i]->hashType == tHash) {
					return (T*)components[i];
				}
			}

			return nullptr;
		}
	};

	class SystemBase {
	public:
		const size_t hashType;
		SystemBase(size_t hashType)
			: hashType{ hashType } {}

		virtual void Update(float elapsedTime) = 0;
		virtual void Render(LPDIRECT3DDEVICE9 device) = 0;
	};

	template <typename TSystem, typename TComponent>
	class System : public SystemBase {
		static_assert(std::is_base_of<ComponentBase, TComponent>::value, "TComponent должен наследовать ECS::Component!");
		//static_assert(std::is_base_of<SystemBase, TSystem>::value, "TSystem должен наследовать ECS::System!");

		TComponent* components[MAX_COMPONENTS]{ 0 };

	protected:
		void GetComponents(__out TComponent*** components) {
			*components = this->components;
		}

		virtual void OnComponentUpdate(TComponent* component, float elapsedTime) {}
		virtual void OnComponentRender(TComponent* component, LPDIRECT3DDEVICE9 device) {}

	public:
		System()
			: SystemBase(GetTypeHash<TSystem>())
		{}
		virtual void Update(float elapsedTime) final {
			for (size_t i = 0; i < MAX_COMPONENTS; i++)
			{
				if (components[i]) {
					OnComponentUpdate(components[i], elapsedTime);
				}
			}
		}
		virtual void Render(LPDIRECT3DDEVICE9 device) final {
			for (size_t i = 0; i < MAX_COMPONENTS; i++)
			{
				if (components[i]) {
					OnComponentRender(components[i], device);
				}
			}
		}

		void Add(TComponent* component) {
			for (size_t i = 0; i < MAX_COMPONENTS; i++)
			{
				if (!components[i]) {
					components[i] = component;
					return;
				}
			}

			throw std::overflow_error("Система не может хранить больше компонентов.");
		}

		template <typename ...Params>
		TComponent* Create(Entity* entity, Params ...params) {
			for (size_t i = 0; i < MAX_COMPONENTS; i++)
			{
				if (!components[i]) {
					auto c = new TComponent(params...);
					components[i] = c;
					c->OnInitialize(entity);
					entity->AddComponent(c);
					return c;
				}
			}
			throw std::overflow_error("Система не может хранить больше компонентов.");
		}

	};

}
