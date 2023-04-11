#include "Object3D.h"

Object3D::Object3D(Mesh mesh, Shader shader, PBRMetallicRoughness material, unsigned int tag) : mesh(mesh), material(material), shader(shader), tag(tag){}

void Object3D::updateUniforms() {
    glUniformMatrix4fv(glGetUniformLocation(shader.getId(), "world"), 4, false, this->transform.worldMatrix().entries);
}

void Object3D::drawObject() {
    glUseProgram(shader.getId());
    glBindVertexArray(mesh.getVao());
    material.useMaterial(shader);
    glUniform1i(glGetUniformLocation(shader.getId(), "dontShade"), tag == Tags::portal? 1 : 0);

    updateUniforms();
    glDrawArrays(GL_TRIANGLES, 0, mesh.drawCount());
}

