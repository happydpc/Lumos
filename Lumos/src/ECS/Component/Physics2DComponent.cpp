#include "lmpch.h"
#include "Physics2DComponent.h"
#include "Maths/MathsUtilities.h"
#include "ECS/EntityManager.h"

#include <imgui/imgui.h>

namespace Lumos
{
    Physics2DComponent::Physics2DComponent()
    {
        m_PhysicsObject = CreateRef<PhysicsObject2D>();
    }
    
	Physics2DComponent::Physics2DComponent(Ref<PhysicsObject2D>& physics)
		: m_PhysicsObject(physics)
	{
	}

	void Physics2DComponent::Update()
	{
        auto angle = m_PhysicsObject->GetAngle();
        auto qw = cos(angle/2);
        auto qz = 1.0f * sin(angle/2);
        
		auto entity = ComponentManager::Instance()->GetComponentArray<Physics2DComponent>()->GetEntity(this);
		entity->GetTransformComponent()->SetLocalPosition(Maths::Vector3(m_PhysicsObject->GetPosition(), 1.0f));
		entity->GetTransformComponent()->SetLocalOrientation(Maths::Quaternion(0.0f, 0.0f, qz, qw));
		entity->GetTransformComponent()->UpdateMatrices();
	}

	void Physics2DComponent::OnImGui()
	{
		auto pos = m_PhysicsObject->GetPosition();
		auto angle = m_PhysicsObject->GetAngle();
		auto friction = m_PhysicsObject->GetFriction();
		auto isStatic = m_PhysicsObject->GetIsStatic();
		auto isRest = m_PhysicsObject->GetIsAtRest();

		auto elasticity = m_PhysicsObject->GetElasticity();
            
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2,2));
        ImGui::Columns(2);
        ImGui::Separator();

        ImGui::AlignTextToFramePadding();
        ImGui::Text("Position");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::DragFloat2("##Position", &pos.x))
            m_PhysicsObject->SetPosition(pos);
            
        ImGui::PopItemWidth();
        ImGui::NextColumn();
            
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Orientation");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::DragFloat("##Orientation", &angle))
            m_PhysicsObject->SetOrientation(angle);
            
        ImGui::PopItemWidth();
        ImGui::NextColumn();
            
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Friction");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::DragFloat("##Friction", &friction))
            m_PhysicsObject->SetFriction(friction);
            
        ImGui::PopItemWidth();
        ImGui::NextColumn();
            
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Elasticity");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::DragFloat("##Elasticity", &elasticity))
            m_PhysicsObject->SetElasticity(elasticity);
            
        ImGui::PopItemWidth();
        ImGui::NextColumn();
            
        ImGui::AlignTextToFramePadding();
        ImGui::Text("Static");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::Checkbox("##Static", &isStatic))
            m_PhysicsObject->SetIsStatic(isStatic);
            
        ImGui::PopItemWidth();
        ImGui::NextColumn();
            
        ImGui::AlignTextToFramePadding();
        ImGui::Text("At Rest");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if(ImGui::Checkbox("##At Rest", &isRest))
            m_PhysicsObject->SetIsAtRest(isRest);
            
        ImGui::PopItemWidth();
        ImGui::NextColumn();
            
        ImGui::Columns(1);
        ImGui::Separator();
        ImGui::PopStyleVar();
	}
}
