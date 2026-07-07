#include "Test.h"
#include "imgui.h"
#include <iostream>

namespace test {
    TestMenu::TestMenu(Test*& currentTestPointer)
        : m_CurrentTest(currentTestPointer)
    {
        
    }

    // displays the button for each registered test and switches to the selected test when the button is clicked
    void TestMenu::OnImGuiRender()
    {  
        for (auto& test : m_Tests){
            if (ImGui::Button(test.first.c_str())){
                // std::cout << "Switching to test: " << test.first << std::endl;
                m_CurrentTest = test.second();
            }
        }
    }
}