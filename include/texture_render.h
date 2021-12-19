#ifndef TEXTURE_RENDER_H
#define TEXTURE_RENDER_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <shader.h>

#include <string>

class TextureRender
{
public:
    unsigned int VAO;

    TextureRender()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 5, NULL, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)0);
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void *)(3 * sizeof(GLfloat)));
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void draw(Shader &shader, GLuint TextureID, GLfloat x, GLfloat y, GLfloat w, GLfloat h, glm::mat4 &model, glm::mat4 &view, glm::mat4 &projection)
    {
        shader.use();
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);
        shader.setMat4("model", model);
        shader.setVec3("textColor", 1.0, 1.0, 1.0);

        GLfloat vertices[6][5] = {
            {x, y + h, 0.0, 0.0, 0.0},
            {x, y, 0.0, 0.0, 1.0},
            {x + w, y, 0.0, 1.0, 1.0},

            {x, y + h, 0.0, 0.0, 0.0},
            {x + w, y, 0.0, 1.0, 1.0},
            {x + w, y + h, 0.0, 1.0, 0.0}};

        glActiveTexture(GL_TEXTURE0);
        glBindVertexArray(VAO);
        glBindTexture(GL_TEXTURE_2D, TextureID);

        // 更新VBO内存的内容
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(GLfloat) * 6 * 5, vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
    }

private:
    unsigned int VBO;
};
#endif