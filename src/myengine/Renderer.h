#ifndef MYENGINE_RENDERER_H
#define MYENGINE_RENDERER_H

#include "Component.h"

#include <rend/rend.h>

#include <memory>

namespace myengine
{

struct Model;
struct ShaderMaterial;
struct ShaderPointLight;

struct Renderer : public Component
{
  void onInitialize();
  void onRender();
  void onTick();

  void shaderSetAll();

  void setShaderMaterial(ShaderMaterial _material);
  void setShaderPointLight(ShaderPointLight _light);

  void setModel(std::shared_ptr<Model> model);
  bool CheckShaderCompiled(GLint shader);

private:
  std::shared_ptr<rend::Shader> shader;
  std::shared_ptr<Model> model;

  rend::vec3 lightPosition;
  bool lightForward = false;

};

struct ShaderMaterial
{
	//rend::vec3 ambient;
	//rend::vec3 diffuse;
	//rend::vec3 specular;

	//float shininess;

	rend::vec3 albedo;
	float metallic;
	float roughness;
	float ao;

	ShaderMaterial()
	{
		//ambient = rend::vec3(0, 0, 0);
		//diffuse = rend::vec3(0.55f, 0.55f, 0.55f);
		//specular = rend::vec3(0.7f, 0.7f, 0.7f);

		//shininess = 32.0f;

		albedo = rend::vec3(1, 0, 1);
		metallic = 0;
		roughness = 0.3;
		ao = 0;
	}
};

struct ShaderPointLight
{
	rend::vec3 colour;

	rend::vec3 ambient;
	rend::vec3 diffuse;
	rend::vec3 specular;

	float constant;
	float linear;
	float quadratic;

	rend::vec3 position;

	ShaderPointLight()
	{
		colour = rend::vec3(1, 1, 1);

		diffuse = colour * rend::vec3(0.5f);
		ambient = diffuse * rend::vec3(0.2f);
		specular = rend::vec3(0.5f, 0.5f, 0.5f);

		constant = 1.0f;
		linear = 0.045f;
		quadratic = 0.0075f;

		position = rend::vec3(0, 0, -5);

		//linear = 0.0014f;
		//quadratic = 0.000007f;
	}

	void SetPosition(rend::vec3 _position)
	{
		position = _position;
	}
};

struct ShaderDirectionalLight
{
	rend::vec3 colour;

	rend::vec3 ambient;
	rend::vec3 diffuse;
	rend::vec3 specular;

	ShaderDirectionalLight()
	{
		colour = rend::vec3(1, 1, 1);

		diffuse = colour * rend::vec3(0.5f);
		ambient = diffuse * rend::vec3(0.2f);
		specular = rend::vec3(1.0f, 1.0f, 1.0f);
	}
};
}


#endif