#include "Object3D.h"

Object3D::Object3D(Mesh& mesh, Shader& shader, PBRMetallicRoughness& material, unsigned int tag) : mesh(mesh), material(material), shader(shader), tag(tag){}

void Object3D::updateUniforms() {
    glUseProgram(shader.getId());
    glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "u_world"), 1, GL_FALSE, this->transform.worldMatrix().entries);
}

void Object3D::drawObject() {
    glUseProgram(shader.getId());
    glBindVertexArray(mesh.getVao());
    material.useMaterial(shader);
    glUniform1i(glGetUniformLocation(shader.getId(), "u_dontShade"), tag == Tags::portal? 1 : 0);

    updateUniforms();
    glDrawElements(GL_TRIANGLES, mesh.drawCount(), GL_UNSIGNED_SHORT, nullptr);
}

