#include "object.h"

Object::Object(Mesh *mesh, Texture *texture, glm::vec3 position, glm::vec3 rotation)
{
    this->id = GetNextId();

    this->mesh = mesh;
    this->texture = texture;
    this->position = position;
    this->rotation = rotation;
    this->scale = glm::vec3(1.0f);
}

Object::Object(Mesh *mesh, Texture *texture, glm::vec3 position)
{
    this->id = GetNextId();
    this->mesh = mesh;
    this->texture = texture;
    this->position = position;
    this->rotation = glm::vec3(0.0f);
    this->scale = glm::vec3(1.0f);
}

Object::Object(Mesh *mesh, Texture *texture)
{
    this->id = GetNextId();
    this->mesh = mesh;
    this->texture = texture;
    this->position = glm::vec3(0.0f);
    this->rotation = glm::vec3(0.0f);
    this->scale = glm::vec3(1.0f);
}

Object::Object(Mesh *mesh)
{
    this->id = GetNextId();
    this->mesh = mesh;
    this->texture = getDefaultTexture();
    this->position = glm::vec3(0.0f);
    this->rotation = glm::vec3(0.0f);
    this->scale = glm::vec3(1.0f);
}

Object::~Object()
{
    delete mesh;
    delete texture;
}

void Object::Render()
{

    mesh->Render();
}

glm::mat4 Object::GetModelMatrix()
{
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, scale);
    return model;
}

void Object::Menu()
{
    if (ImGui::CollapsingHeader(("Object " + std::to_string(GetId())).c_str()))
    {
        ImGui::SliderFloat3(("Position##" + std::to_string(GetId())).c_str(), &position.x, -10.0f, 10.0f);
        ImGui::SliderFloat3(("Rotation##" + std::to_string(GetId())).c_str(), &rotation.x, -180.0f, 180.0f);
        ImGui::SliderFloat3(("Scale##" + std::to_string(GetId())).c_str(), &scale.x, 0.0f, 10.0f);

        if (ImGui::Button(("Reset##" + std::to_string(GetId())).c_str()))
        {
            position = glm::vec3(0.0f);
            rotation = glm::vec3(0.0f);
            scale = glm::vec3(1.0f);
        }
    }
}

void Object::ObjectCreationMenu(std::vector<Object *> &objects)
{
    if (ImGui::CollapsingHeader("Object Creation"))
    {
        if (ImGui::Button("Create Triangle"))
        {
            objects.push_back(new Object(Mesh::CreateTriangle()));
        }
        if (ImGui::Button("Create Quad"))
        {
            objects.push_back(new Object(Mesh::CreateQuad()));
        }
        if (ImGui::Button("Create Cube"))
        {
            objects.push_back(new Object(Mesh::CreateCube()));
        }
        if (ImGui::Button("Create Sphere"))
        {
            objects.push_back(new Object(Mesh::CreateSphere(20, 20)));
        }
    }
}
