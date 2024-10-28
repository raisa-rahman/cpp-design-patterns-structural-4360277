#include <iostream>
#include <memory>  // For std::unique_ptr and std::make_unique

using namespace std;

// Component interface
class Component
{
public:
    virtual void run() = 0;   // Pure virtual function, must be implemented
    virtual ~Component() = default;  // Virtual destructor for proper cleanup
};

// Concrete implementation A
class ConcreteComponentA : public Component
{
public:
    void run() override
    {
        cout << "Executing ConcreteComponentA::run()" << endl;
    }
};

// Concrete implementation B
class ConcreteComponentB : public Component
{
public:
    void run() override
    {
        cout << "Executing ConcreteComponentB::run()" << endl;
    }
};

// Incompatible class (legacy component)
class LegacyComponent
{
public:
    void go()
    {
        cout << "Executing LegacyComponent::go()" << endl;
    }
};

// Adapter to make LegacyComponent compatible with Component interface
class LegacyAdapter : public Component
{
public:
    LegacyAdapter() : m_adaptee(make_unique<LegacyComponent>()) {}

    void run() override
    {
        cout << "LegacyAdapter::run() -> Calling LegacyComponent::go()" << endl;
        m_adaptee->go();  // Adapted call
    }

private:
    unique_ptr<LegacyComponent> m_adaptee;  // Composition: wraps the LegacyComponent
};

// Main function
int main()
{
    // Creating components
    const unique_ptr<Component> components[] = {
        make_unique<ConcreteComponentA>(),   // Concrete component A
        make_unique<ConcreteComponentB>(),   // Concrete component B
        make_unique<LegacyAdapter>()         // Adapter for the legacy component
    };

    // Loop through each component and call run
    for (const auto& component : components)
    {
        component->run();  // Call the appropriate run method for each
    }

    return 0;
}
