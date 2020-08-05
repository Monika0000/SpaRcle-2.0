--local sr = require "mymodule"
--module("mymodule", package.seeall)
    --Debug.Log("hello")
    --Debug.Error("Fail")

function Start ()
    sphere   = Engine.LoadPrefab("Sphere")
    sphere:SetPosition(10,0,0)
    
    sphere2  = Engine.LoadPrefab("Sphere")
    sphere2:SetPosition(14, 0,0)
        
    light    = Engine.LoadPrefab("Engine/Lump")
    light:SetScale(0.3, 0.3, 0.3)
    light:AddPointLight(PointLight.new())
    --light:AddDirectionalLight(DirectionalLight.new())
    --sina     = Engine.LoadPrefab("Sphere") 

   -- sina:SetScale(0.3, 0.3, 0.3)
end;

function Update ()
    --Debug.Log(math.sin(Time))
    --print(math.sin(math.floor(Time)))

    local v = math.cos(Time) / 250.0
    sphere:Move(0,0,v)
    
    sphere2:Rotate(0.03,0.03,0.03)
end;

