#include "ConveyorBelt.h"
#include "Factory.h"

ConveyorBelt::ConveyorBelt(Context* context) : LogicComponent(context) {}

ConveyorBelt::ConveyorBelt(Context* context, Factory* factory, Node* node, String materialName, String name, ConfigFile* iniFile) : LogicComponent(context)
{
    name_ = name;
    node_ = node;
    context_ = context;
    materialName_ = materialName;
    factory_ = factory;

    auto* cache = context->GetSubsystem<ResourceCache>();
    cache_ = cache;

    LoadParameters(iniFile);

    if(node)
    {
        Vector3 scale = node->GetScale();
        scale.z_ -= scale.y_;
        scale.x_ -= 0.01f;
        node->SetScale(scale);

        size_ = node->GetScale();
        size_.x_ -= 0.01f;
        size_.y_ += 0.01f;
    }

    Vector3 cylinderSize = Vector3( size_.y_, size_.x_, size_.y_ );
    cylinderSize += Vector3( -0.01f, 0.02f, -0.01f );

    for( int i = 0 ; i < 2 ; i++ )
    {
        nodeCylinders_[i] = factory_->scene_->CreateChild("Cylinder"+i);

        nodeCylinders_[i]->SetRotation(node->GetRotation());
        nodeCylinders_[i]->Roll(-90.0f);

        nodeCylinders_[i]->SetScale( cylinderSize );

        if(i==0) nodeCylinders_[i]->SetPosition(node->GetPosition() + node->GetRotation()*Vector3(0,0,0.5f*size_.z_));
        if(i==1) nodeCylinders_[i]->SetPosition(node->GetPosition() - node->GetRotation()*Vector3(0,0,0.5f*size_.z_));



        auto* model = nodeCylinders_[i]->CreateComponent<StaticModel>();
        model->SetModel(cache->GetResource<Model>("Models/Cylinder.mdl"));
        model->SetMaterial(cache->GetResource<Material>("Data2/Materials/CircleCross01.xml"));
        model->SetCastShadows(true);

        // Create physics components, use a smaller mass also
        auto* body = nodeCylinders_[i]->CreateComponent<RigidBody>();
        //body->SetMass( cylinderSize.x_ * cylinderSize.y_ * cylinderSize.z_ * 1000.0f );
        body->SetMass( 0.0f );
        body->SetFriction(0.6f);
        auto* shape = nodeCylinders_[i]->CreateComponent<CollisionShape>();
        shape->SetCylinder (1.0f, 1.0f);
    }

    // Create one model and a StaticModel to display it from scratch
    // Note: there are duplicated vertices to enable face normals. We will calculate normals programmatically
    //{
    const unsigned numVertices = 36;

    float r = 0.5f * size_.y_;
    float l = 0.5f * size_.z_;
    float w = 0.49f * size_.x_;

    int n = 18-1;

    float vertexData[] =
    {
        // Position             Normal                  UV
        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,


        // Position             Normal
        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,

        -l  ,  0.0f,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,    -r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f,
        -l-r,     r,     w,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f
    };

    float deltaAngle = 360.0f / ( n - 2 );

    int i = 0;

    int m = 16;

    vertexData[m*i+0] =  0; //Pos
    vertexData[m*i+1] = -r;
    vertexData[m*i+2] =  -w;

    vertexData[m*i+3] = 0.0f;//Normal
    vertexData[m*i+4] = -1.0f;
    vertexData[m*i+5] = 0.0f;

    vertexData[m*i+6] = 0; // UV
    vertexData[m*i+7] = 0;


    vertexData[m*i+8] =  0;//Pos
    vertexData[m*i+9] = -r;
    vertexData[m*i+10] =  w;

    vertexData[m*i+11] = 0.0f;//Normal
    vertexData[m*i+12] = 1.0f;
    vertexData[m*i+13] = 0.0f;

    vertexData[m*i+14] = 0;//UV
    vertexData[m*i+15] = w;

    float u = 0.0f;

    for(int i=1; i<n; i++)
    {
        float angle = (i-1)*deltaAngle;

        float x;

        if(angle > 180.0f)
        {
            x = -l;
        }
        else
        {
            x =  l;
        }

        if(i==1)
            u = x;
        if((i>1) and (i<9))
            u = x - (angle/360)*2*M_PI*r;
        //if(i==9)
        // u = 2*x + (angle/360)*2*M_PI*r;
        if((i>=9) and (i<18) )
            u = 2*x - (angle/360)*2*M_PI*r;


        vertexData[m*i+0] = -x-r*Sin(angle);
        vertexData[m*i+1] =   -r*Cos(angle);
        vertexData[m*i+2] = -w;

        vertexData[m*i+3] = -Sin(angle);
        vertexData[m*i+4] = -Cos(angle);
        vertexData[m*i+5] = 0.0f;

        vertexData[m*i+6] = u;//UV
        vertexData[m*i+7] = 0.0f;

        vertexData[m*i+8] = -x-r*Sin(angle);
        vertexData[m*i+9] =   -r*Cos(angle);
        vertexData[m*i+10] = w;

        vertexData[m*i+11] = -Sin(angle);
        vertexData[m*i+12] = -Cos(angle);
        vertexData[m*i+13] = 0.0f;

        vertexData[m*i+14] = u;//UV
        vertexData[m*i+15] = w;
    }

    i = n; // last points

    vertexData[m*i+0] =  0; //Pos
    vertexData[m*i+1] = -r;
    vertexData[m*i+2] =  -w;

    vertexData[m*i+3] = 0.0f;//Normal
    vertexData[m*i+4] = -1.0f;
    vertexData[m*i+5] = 0.0f;

    vertexData[m*i+6] = 0; // UV
    vertexData[m*i+7] = 0;


    vertexData[m*i+8] =  0;//Pos
    vertexData[m*i+9] = -r;
    vertexData[m*i+10] =  w;

    vertexData[m*i+11] = 0.0f;//Normal
    vertexData[m*i+12] = 1.0f;
    vertexData[m*i+13] = 0.0f;

    vertexData[m*i+14] = 0;//UV
    vertexData[m*i+15] = w;

    const unsigned short indexData[] =
    {
        0, 1, 2,
        3, 4, 5,
        6, 7, 8,
        9, 10, 11,
        12, 13, 14,
        15, 16, 17,

        18, 19, 20,
        21, 22, 23,
        24, 25, 26,
        27, 28, 29,
        30, 31, 32,
        33, 34, 35
    };

    SharedPtr<Model> fromScratchModel(new Model(context_));
    SharedPtr<VertexBuffer> vb(new VertexBuffer(context_));
    SharedPtr<IndexBuffer> ib(new IndexBuffer(context_));
    SharedPtr<Geometry> geom(new Geometry(context_));

    // Shadowed buffer needed for raycasts to work, and so that data can be automatically restored on device loss
    vb->SetShadowed(true);
    // We could use the "legacy" element bitmask to define elements for more compact code, but let's demonstrate
    // defining the vertex elements explicitly to allow any element types and order
    PODVector<VertexElement> elements;
    elements.Push(VertexElement(TYPE_VECTOR3, SEM_POSITION));
    elements.Push(VertexElement(TYPE_VECTOR3, SEM_NORMAL));

    elements.Push(VertexElement(TYPE_VECTOR2, SEM_TEXCOORD));

    vb->SetSize(numVertices, elements);
    vb->SetData(vertexData);

    ib->SetShadowed(true);
    ib->SetSize(numVertices, false);
    ib->SetData(indexData);

    geom->SetVertexBuffer(0, vb);
    geom->SetIndexBuffer(ib);

    geom->SetDrawRange(TRIANGLE_STRIP, 0, numVertices);

    fromScratchModel->SetNumGeometries(1);
    fromScratchModel->SetGeometry(0, 0, geom);
    fromScratchModel->SetBoundingBox(BoundingBox(Vector3(-l-r, -r, -w), Vector3(l+r, r, w)));

    // Though not necessary to render, the vertex & index buffers must be listed in the model so that it can be saved properly
    Vector<SharedPtr<VertexBuffer> > vertexBuffers;
    Vector<SharedPtr<IndexBuffer> > indexBuffers;
    vertexBuffers.Push(vb);
    indexBuffers.Push(ib);
    // Morph ranges could also be not defined. Here we simply define a zero range (no morphing) for the vertex buffer
    PODVector<unsigned> morphRangeStarts;
    PODVector<unsigned> morphRangeCounts;
    morphRangeStarts.Push(0);
    morphRangeCounts.Push(0);
    fromScratchModel->SetVertexBuffers(vertexBuffers, morphRangeStarts, morphRangeCounts);
    fromScratchModel->SetIndexBuffers(indexBuffers);


    Node* node2 = nullptr;

    if(node)
    {
        node2 = factory_->scene_->CreateChild("FromScratchObject");
        node2->SetPosition(node->GetPosition());
        node2->SetRotation(node->GetRotation());
        node2->Yaw(-90.0f);
    }

    auto* object = node2->CreateComponent<StaticModel>();

    object->SetModel(fromScratchModel);

    Material* material = cache->GetResource<Material>(materialName);

    object->SetMaterial(cache->GetResource<Material>("Data2/Materials/ScrollingTexture03.xml"));
    material->SetShaderParameter("ScrollingSpeed", 2.35f);

    object->SetMaterial(material);

    CollisionShape* collision = new CollisionShape(context);
}

ConveyorBelt::~ConveyorBelt()
{
}

void ConveyorBelt::RegisterObject(Context* context)
{
    context->RegisterFactory<ConveyorBelt>();
}

void ConveyorBelt::LoadParameters(ConfigFile* iniFile)
{
    if(iniFile)
    {
        width_       = iniFile->GetInt   (name_, "Width",      200   );
        length_      = iniFile->GetInt   (name_, "Length",     6000  );
        radius_      = iniFile->GetInt   (name_, "Radius",     100   );
        speed_       = iniFile->GetInt   (name_, "Speed",      220   );
        friction_    = iniFile->GetFloat (name_, "Friction",   0.5   );
        SetSpeed(iniFile->GetInt   (name_, "Speed",      220   ));
    }
}

Vector3 ConveyorBelt::GetPosition()
{
    return body_->GetPosition();
}

Vector2 ConveyorBelt::GetPosition2D()
{
    return Factory::To2D(GetPosition());
}

void ConveyorBelt::SetSpeed(float speed)
{
    ResourceCache* cache = nullptr;

    if(context_)
        cache = context_->GetSubsystem<ResourceCache>();

    Material* material = nullptr;

    if(cache)
        material = cache->GetResource<Material>(materialName_);

    if(material)
        material->SetShaderParameter("ScrollingSpeed", speed/40.0f);

    speed_ = speed;
}

void ConveyorBelt::Update(float dt)
{

    float r = 0.1f;
    //float deltaAngle = speed_ * 180.0f / (M_PI * r);
    float deltaAngle = speed_ / r;

    for(int i=0; i<2; i++) nodeCylinders_[i]->Yaw( deltaAngle * dt);
}
