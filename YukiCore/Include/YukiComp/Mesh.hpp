/**
 * ===========================================
 * Author:          vn-vna (Anh Vu)
 * Country:         Vietnam
 * License:         MIT
 * ===========================================
 */

#pragma once

#include "YukiComp/Mesh.hpp"
#include "YukiCore/Objects.hpp"
#include "YukiCore/Graphics.hpp"
#include "YukiCore/Headers.hpp"

namespace Yuki::Comp
{

using Core::IOGLElementBuffer;
using Core::IOGLShaderProgram;
using Core::IOGLTexture;
using Core::IOGLVertexArray;
using Core::IOGLVertexBuffer;
using Core::ISharedObject;
using Core::PrimitiveTopology;

typedef struct StVertexFormat
{
  Vec3F position;
  Vec3F normal;
  Vec2F texcoord;

  StVertexFormat(
      const Vec3F& position, // position
      const Vec3F& normal,   //
      const Vec2F& texcoord  //
  )
      : position(position),
        normal(normal),
        texcoord(texcoord)
  {}

  StVertexFormat()
      : position(0, 0, 0),
        normal(0, 0, 0),
        texcoord(0, 0)
  {}

} MeshVertexFormat;

// Index data format
typedef struct StIndexData
{
  PrimitiveTopology topology;
  Vector<unsigned>  data;
} MeshIndexData;

/**
 * Struct that use to destruct the model matrix to separate
 * properties.
 */
typedef struct StTransformationInfo
{
  Vec3F       scale;
  QuaternionF rotation;
  Vec3F       translation;
  Vec3F       skew;
} TransformationInfo;

/**
 * Every mesh need a specific material to be rendered.
 * Maybe plastic, metal, or something else
 * @TODO Material class need to be improved in the future.
 */
class IMaterial : virtual public ISharedObject
{
public:
  virtual SharedPtr<IOGLTexture> GetSpecularMap() = 0;
  virtual SharedPtr<IOGLTexture> GetAmbientMap()  = 0;
  virtual SharedPtr<IOGLTexture> GetDiffuseMap()  = 0;

  virtual void SetSpecularMap(SharedPtr<IOGLTexture> specmap) = 0;
  virtual void SetAmbientMap(SharedPtr<IOGLTexture> ambmap)   = 0;
  virtual void SetDiffuseMap(SharedPtr<IOGLTexture> diffmap)  = 0;
};

/**
 * A 3D game often load the models from external 3D modeling
 * programs. Class IMesh is here to store them in a
 * "pretty" structure that will be used by IModel
 * @TODO Mesh class is very simple now, it must be improved
 * @TODO Some memory leak detected, it's caused by Assimp loader
 * much more.
 */
class IMesh : virtual public ISharedObject
{
public:
  virtual SharedPtr<IOGLTexture>          GetMeshTexture() const        = 0;
  virtual SharedPtr<IOGLElementBuffer>    GetElementBuffer() const      = 0;
  virtual SharedPtr<IOGLVertexBuffer>     GetVertexBuffer() const       = 0;
  virtual SharedPtr<IOGLVertexArray>      GetVertexArray() const        = 0;
  virtual SharedPtr<IMaterial>            GetMaterial() const           = 0;
  virtual const PrimitiveTopology&        GetTopology() const           = 0;
  virtual const String&                   GetName() const               = 0;
  virtual const Mat4F&                    GetMeshMatrix() const         = 0;
  virtual const Vector<MeshVertexFormat>& GetVertexData() const         = 0;
  virtual const MeshIndexData&            GetIndexData() const          = 0;
  virtual TransformationInfo              GetTransformationInfo() const = 0;

  virtual void SetMaterial(SharedPtr<IMaterial> material)          = 0;
  virtual void SetMeshMatrix(const Mat4F& matrix)                  = 0;
  virtual void SetTranslation(const Vec3F& position)               = 0;
  virtual void SetRotation(const Vec3F& axis, float rotationAngle) = 0;
  virtual void SetScale(const Vec3F& scaleVector)                  = 0;
  virtual void TranslateMesh(const Vec3F& direction)               = 0;
  virtual void RotateMesh(const Vec3F& axis, float rotationAngle)  = 0;
  virtual void ScaleMesh(const Vec3F& scaleVector)                 = 0;

  virtual void
  RenderMesh(SharedPtr<ICamera> pCamera, SharedPtr<IScene> pScene) const = 0;
};

/**
 * This function is used to created a new interface instance
 * of a Mesh
 * @param vertexData an array of VertexFormat that stores
 * vertices info of the mesh
 * @param indexData indices data of the mesh
 * @param texture can be NO_TEXTURE
 * @param material a material
 * @param meshName provide a name for it
 * @return an interface instance for the mesh
 */
SharedPtr<IMesh> GenerateYukiMesh(
    Vector<MeshVertexFormat>&    vertexData, // An array of vertices array
    MeshIndexData&               indexData,  // Indices format of the mesh
    SharedPtr<Core::IOGLTexture> texture,    // The mesh texture
    SharedPtr<IMaterial>         material,   // Material
    const String&                meshName    // Name
);

/**
 * This function is used to create a new material and return
 * it's interface instance
 * @param specular Specular strength
 * @param ambient Ambient strength
 * @return an interface instance of the material
 * @TODO Provide a method to create material from ambient
 * map or specular map in the future.
 */
SharedPtr<IMaterial> GenerateSolidMaterial(
    const Vec4F& ambient, const float specular, const float diffuse
);

} // namespace Yuki::Comp
