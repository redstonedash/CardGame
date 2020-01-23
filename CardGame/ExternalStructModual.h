#pragma once
flecs::component<Transform> Transform_c(world, "Transform");
flecs::component<Model> Model_c(world, "Model");
flecs::component<BoundingBox> BoundingBox_c(world, "BoundingBox");
flecs::component<Shader> Shader_c(world, "Shader");
flecs::component<Color> Color_c(world, "Color");
flecs::component<Rectangle> Rectangle_c(world, "Rectangle");
flecs::component<RenderTexture> RenderTexture_c(world, "RenderTexture");
flecs::component<Matrix> Matrix_c(world, "Matrix");
flecs::component<Camera> Camera_c(world, "Camera");