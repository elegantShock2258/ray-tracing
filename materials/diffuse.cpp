#pragma once
#include "material.cpp"

class Diffuse : public Material{
    public:
    Diffuse(){
        this->name = "Diffuse";
    }
    Color getMaterialColor(const Point &center, const Ray &ray, int res){
        
    }
};