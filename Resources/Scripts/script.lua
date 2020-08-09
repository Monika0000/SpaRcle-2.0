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
    light    = PointLight.new()
    light:SetIntensity(5)
    lump:AddPointLight(light)

    mat   = Material.Load("Brick")
    model = Model.LoadOBJWithMat("plane", mat)
    gm    = World.Instantiate("Plane", model)
    gm:SetPosition(-0.5,0,0)

    model2 = Model.LoadOBJWithMat("plane", mat)
    gm2    = World.Instantiate("Plane2", model2)
    gm2:SetPosition(-0.5,0,-2)

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
    
    sphere2:Rotate(0.03,0.03,0.03)
    sina:Rotate(0,0.02, 0)
    --gm:Rotate(0,v*5.0,0)
end;

