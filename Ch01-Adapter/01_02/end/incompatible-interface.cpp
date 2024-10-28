#include <iostream>
#include <memory>

using namespace std;

class Component
{
public:
    virtual void run() = 0;
    virtual ~Component() = default;
};

class ConcreteComponentA : public Component
{
public:
    virtual void run() override
    {
        cout << "Executing ConcreteComponentA::run()" << endl;
    }
};

class ConcreteComponentB : public Component
{
public:
    virtual void run() override
    {
        cout << "Executing ConcreteComponentB::run()" << endl;
    }
};

// Incompatible class (Legacy)
class LegacyComponent
{
public:
    void go()
    {
        cout << "Executing LegacyComponent::go()" << endl;
    }
};

// Adapter class that makes LegacyComponent compatible with Component
class LegacyComponentAdapter : public Component
{
private:
    unique_ptr<LegacyComponent> legacyComponent;

public:
    LegacyComponentAdapter(unique_ptr<LegacyComponent> legacyComp)
        : legacyComponent(move(legacyComp)) {}

    virtual void run() override
    {
        legacyComponent->go(); // Call the incompatible method inside the adapter
    }
};

int main()
{
    const unique_ptr<Component> components[]
    {
        make_unique<ConcreteComponentA>(),
        make_unique<ConcreteComponentB>(),
        // Use the adapter to wrap LegacyComponent
        make_unique<LegacyComponentAdapter>(make_unique<LegacyComponent>())
    };

    for (const auto& component : components)
    {
        component->run();
    }

    return 0;
}
