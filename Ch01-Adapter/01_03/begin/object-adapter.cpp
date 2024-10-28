#include <iostream>
#include <memory>

using namespace std;

class Component
{
public:
    virtual void run() = 0;  // Pure virtual function
    virtual ~Component() = default;  // Virtual destructor for cleanup
};

// Incompatible class
class LegacyComponent
{
public:
    void go()
    {
        cout << "Executing LegacyComponent::go()" << endl;
    }    
};

// Object Adapter (composition-based)
class LegacyAdapter : public Component
{
public:
    LegacyAdapter() : m_adaptee(make_unique<LegacyComponent>()) {}

    virtual void run() override
    {
        cout << "LegacyAdapter::run() -> calling LegacyComponent::go()" << endl;
        m_adaptee->go();  // Delegates to LegacyComponent
    }

private:
    unique_ptr<LegacyComponent> m_adaptee;
};

// Class Adapter (inheritance-based)
class LegacyClassAdapter : public Component, private LegacyComponent
{
public:
    virtual void run() override
    {
        cout << "LegacyClassAdapter::run() -> calling LegacyComponent::go()" << endl;
        go();  // Directly calls go() since it inherits LegacyComponent
    }
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

int main()
{
    // Array of components, each demonstrating polymorphism
    const unique_ptr<Component> components[]
    {
        make_unique<ConcreteComponentA>(),
        make_unique<ConcreteComponentB>(),
        make_unique<LegacyAdapter>(),      // Object Adapter usage
        make_unique<LegacyClassAdapter>()  // Class Adapter usage
    };
    
    // Iterate through each component and call its run method
    for (const auto& component : components)
    {
        component->run();
    }

    return 0;
}
