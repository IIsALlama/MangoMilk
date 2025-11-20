
#include "game_render.h"

GLsizei W = 800;
GLsizei H = 600;

unsigned int frameBuffer;
unsigned int renderBuffer;

namespace MangoMilk {
    namespace GameRender {

        unsigned int outputTexture;

        void Initialize()
        {
            glGenFramebuffers(1, &frameBuffer);
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

            glGenTextures(1, &outputTexture);
            glBindTexture(GL_TEXTURE_2D, outputTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTexture, 0);

            glGenRenderbuffers(1, &renderBuffer);
            glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, W, H);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
                std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindRenderbuffer(GL_RENDERBUFFER, 0);
        }

        void Terminate()
        {
            glDeleteFramebuffers(1, &frameBuffer);
            glDeleteTextures(1, &outputTexture);
            glDeleteRenderbuffers(1, &renderBuffer);
        }

        void _BindFramebuffer()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
        }

        void _UnbindFramebuffer()
        {
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }

        void Rescale(float width, float height)
        {
            GLsizei _w = (GLsizei)width;
            GLsizei _h = (GLsizei)height;
            glBindTexture(GL_TEXTURE_2D, outputTexture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _w, _h, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, outputTexture, 0);

            glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _w, _h);
            glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);
        }

        void Render()
        {
            _BindFramebuffer();

            vector<Entity*> entities = GameManager::GetEntities();
            for (size_t i = 0; i < entities.size(); i++)
            {
                Entity* entity = entities[i];
                Vector2 pos = entity->transform->position;
                Vector2 scale = entity->transform->scale;

                glBegin(GL_TRIANGLES);
                glVertex2f(pos.x-0.5f * scale.x, pos.y-0.5f * scale.y);
                glVertex2f(pos.x-0.5f * scale.x, pos.y+0.5f * scale.y);
                glVertex2f(pos.x+0.5f * scale.x, pos.y-0.5f * scale.y);
                glEnd();

                glBegin(GL_TRIANGLES);
                glVertex2f(pos.x - 0.5f * scale.x, pos.y + 0.5f * scale.y);
                glVertex2f(pos.x + 0.5f * scale.x, pos.y + 0.5f * scale.y);
                glVertex2f(pos.x + 0.5f * scale.x, pos.y - 0.5f * scale.y);
                glEnd();
            }

            _UnbindFramebuffer();
        }
    }

}
