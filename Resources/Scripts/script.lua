--local sr = require "mymodule"
--module("mymodule", package.seeall)
    --Debug.Log("hello")
    --Debug.Error("Fail")

function Start ()
    sphere   = Engine.LoadPrefab("Sphere")
    sphere:SetPosition(10,0,0)
    
    sphere2  = Engine.LoadPrefab("Sphere")
    sphere2:SetPosition(14, 0,0)
        
    lump     = Engine.LoadPrefab("Engine/Lump")
    lump:SetScale(0.3, 0.3, 0.3)
    lump:SetPosition(0,0,3)
    lump:Rotate(0,0,0)
    light    = PointLight.new()
    light:SetIntensity(5)
    lump:AddPointLight(light)

    mat    = Material.Load("Brick")
    model  = Model.LoadOBJWithMat("plane", mat)
    gm     = World.Instantiate("Plane", model)
    gm:SetPosition(-0.5,0,0)

    model2  = Model.LoadOBJWithMat("plane", mat)
    gm2     = World.Instantiate("Plane", model2)
    gm2:SetPosition(-0.5,2,0)

    --fbx    = Model.LoadFBXWithMat("cube", mat)
    --gm2    = World.Instantiate("fbx", fbx)
    --gm2:SetPosition(0,0,600)
    --gm2:SetScale(0.00001, 0.00001, 0.00001)

    --fbx2   = Model.LoadFBX("Dentist")
    --dentist= World.Instantiate("dentist", fbx2)
    --dentist:SetPosition(5,0,5)

    --fbx3   = Model.LoadFBX("Player")
    --table= World.Instantiate("Player", fbx3)
    --table:SetPosition(-15,0,5)
    --size = 0.05;
    --table:SetScale(size, size, size)
    
    --fbx2   = Model.LoadFBX("objects")
    --objects= World.Instantiate("objects", fbx2)
    --objects:SetPosition(5,3,5)
    --size   = 0.01;
    --objects:SetScale(size, size, size)

    fbx2   = Model.LoadFBX("plane_bone")
    objects= World.Instantiate("plane_bone", fbx2)
    objects:SetPosition(5,3,5)
    size   = 0.01;
    objects:SetScale(size, size, size)

    --model = Model.LoadOBJ("sina")
    --sina  = World.Instantiate("Sina", model)
    --

    sina     = Engine.LoadPrefab("Sina") 
    --sina:SetActive(false)
    sina:SetScale(0.05, 0.05, 0.05)
    sina:SetPosition(0,-5,-5)
end;

function Update ()
    --Debug.Log(math.sin(Time))
    --print(math.sin(math.floor(Time)))

    local v = math.cos(Time) / 250.0
    sphere:Move(0,0,v)
    
    sphere2:Rotate(0.01,0.01,0.01)
    --sina:Rotate(0,0.02, 0)
    --objects:Rotate(0.01,0.01,0.01)
    --vertex:SetPosition(0, v, 0)
    --mesh:SetBind(false)
    --light:SetDiffuse(0.3, math.cos(Time) / 4.0, 0.3)
    --gm:Rotate(0,v*5.0,0)
end;

