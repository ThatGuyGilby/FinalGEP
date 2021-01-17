#include "Renderer.h"
#include "Core.h"
#include "Transform.h"
#include "Resources.h"
#include "Entity.h"
#include "Exception.h"
#include "Camera.h"
#include "Model.h"

#include <fstream>
#include <string>
#include <iostream>

namespace myengine
{

void Renderer::onInitialize(std::string modelPath)
{
	std::shared_ptr<Model> cm = getCore()->getResources()->load<Model>("../models/" + modelPath);
	setModel(cm);

	shader = getCore()->context->createShader();

	shader->parse(
		"../shaders/VertShader.glshader",
		"../shaders/FragShader.glshader"
	);

	lightPosition = rend::vec3(0, 0, -5);
	lightForward = true;
}

void Renderer::onTick()
{
	if (lightForward)
	{
		if (lightPosition.z > -8)
		{
			lightPosition.z -= 0.05;
		}
		else
		{
			lightForward = false;
		}
	}
	else
	{
		if (lightPosition.z < -5)
		{
			lightPosition.z += 0.05;
		}
		else
		{
			lightForward = true;
		}
	}

	//lightForward = true;
	//if (lightForward) lightPosition.z -= 0.01f;
	//else lightPosition.z += 0.01f;

	//if (lightPosition.z < -10) lightForward = false;
	//if (lightPosition.z > 0) lightForward = true;
}

void Renderer::onRender()
{
  if(!model) return;

  shaderSetAll();

  std::shared_ptr<Camera> c = getCore()->getCamera();

  // iterate model parts
  //   set shader texture = part->texture
  //   render

  if(c->getRenderTexture())
  {
    shader->render(c->getRenderTexture());
  }
  else
  {
    shader->render();
  }
}

void Renderer::shaderSetAll()
{
	shader->setMesh(model->mesh);

	shader->setUniform("u_Projection", rend::perspective(rend::radians(45.0f),
		1.0f, 0.1f, 100.0f));

	shader->setUniform("u_View", getCore()->getCamera()->getView());
	shader->setUniform("u_Model", getEntity()->getTransform()->getModel());

	//rend::vec3 lightPos(0, 0, 0);
	//shader->setUniform("lightPos", lightPos);

	shader->setUniform("viewPos", getEntity()->getCore()->getCamera()->getTransform()->position);

	ShaderMaterial testMaterial;
	setShaderMaterial(testMaterial);

	ShaderPointLight testLight;

	testLight.SetPosition(lightPosition);

	setShaderPointLight(testLight);
	//shader->setSampler("u_Texture", texture->internal);
}

void Renderer::setShaderMaterial(ShaderMaterial _material)
{
	//shader->setUniform("material.ambient", _material.ambient);
	//shader->setUniform("material.diffuse", _material.diffuse);
	//shader->setUniform("material.specular", _material.specular);
	//shader->setUniform("material.shininess", _material.shininess);

	shader->setUniform("material.albedo", _material.albedo);

	shader->setUniform("material.metallic", _material.metallic);
	shader->setUniform("material.roughness", _material.roughness);
	shader->setUniform("material.ao", _material.ao);
}

void Renderer::setShaderPointLight(ShaderPointLight _light)
{
	//shader->setUniform("pointLight.ambient", _light.ambient);
	//shader->setUniform("pointLight.diffuse", _light.diffuse);
	//shader->setUniform("pointLight.specular", _light.specular);

	shader->setUniform("pointLight.constant", _light.constant);
	shader->setUniform("pointLight.linear", _light.linear);
	shader->setUniform("pointLight.quadratic", _light.quadratic);

	shader->setUniform("pointLight.position", _light.position);

	shader->setUniform("pointLight.color", _light.colour);
}

void Renderer::setModel(std::shared_ptr<Model> model)
{
  this->model = model;
}
}