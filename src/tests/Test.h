#pragma once

#include <functional>
#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>

namespace test {

    class Test
    {
    public:
        Test() {}
        virtual ~Test() {}

        virtual void OnUpdate(float deltaTime) {}
        virtual void OnRender() {}
        virtual void OnImGuiRender() {}
    };
    
    class TestMenu : public Test
    {
        private:
            // we can modify the pointer itself rather than the object it points to (with the & operator/reference)
            Test*& m_CurrentTest;
            std::vector<std::pair<std::string, std::function<Test*()>>> m_Tests;
            
        public:
            TestMenu(Test*& currentTestPointer);
            void OnImGuiRender() override;

            template<typename T>
            void RegisterTest(const std::string& name){
                for (const auto& test : m_Tests) {
                    if (test.first == name) {
                        throw std::runtime_error("Test already registered with name: " + name);
                    }
                }
                std::cout << "Registering test: " << name << std::endl;
                m_Tests.push_back(std::make_pair(name, []() { return new T(); })); // { name, labda to create new T instance }
            }
    };
}