#ifndef _interpolator_hermite_
#define _interpolator_hermite_

#include <string>
#include <vector>
#include <Eigen/Dense>
#include "interpolator.h"

//--------------------------------
// Hermite 
//--------------------------------

class InterpolatorHermite : public Interpolator
{
public:
    InterpolatorHermite() : Interpolator("Hermite"), mClampDir(glm::vec3(1,0,0)) {}

    virtual glm::vec3 interpolate(int segment, double u) const {
        u = (float)u;
       glm::vec3 p0 = mCtrlPoints.at(segment*2);
       glm::vec3 p0prime = mCtrlPoints.at(segment*2+1);
       glm::vec3 p1 = mCtrlPoints.at(segment*2+2);
       glm::vec3 p1prime = mCtrlPoints.at(segment*2+3);
       float h0 = 1.0f - 3.0f*(float)pow(u,2) + 2.0f*(float)pow(u,3);
       float h1 = u * (float)pow((1.0f-u),2);
       float h2 = -1.0f * (float)pow(u,2) + (float)pow(u,3);
       float h3 = 3.0f * (float)pow(u,2) - 2.0f * (float)pow(u,3);
       glm::vec3 fin = p0*h0 + p0prime*h1 + p1prime*h2 + p1*h3;
       return fin;
    }

    virtual void computeControlPoints(const std::vector<glm::vec3>& keys) {
        Eigen::MatrixXd A(keys.size(), keys.size());
        Eigen::MatrixXd p(keys.size(),2);
        Eigen::MatrixXd pPrime(keys.size(), 2);
        //populate clamped matrix
        if (isClamped()){
            A(0,0) = 1.0f;
            A(keys.size()-1,keys.size()-1) = 1.0f;
            for (int i = 1; i < keys.size(); i++){
                A(0,i) = 0.0f;
            }
            for (int i = 0; i < keys.size()-2; i++){
                A(keys.size()-1,i) = 0.0f;
            }
        }
        for (int i = 1; i < keys.size()-1; i++){
            for (int j = 0; j < keys.size(); j++){
                if (i == j+1 || i+1 == j) {
                    A(i, j) = 1.0f;
                }
                else if (i == j) {
                    A(i, j) = 4.0f;
                }
                else {
                    A(i, j) = 0.0f;
                }
            }
        }
        
        if(isClamped()){
            p(0,0) = 1.0f;
            p(0,1) = 0.0f;
            p(keys.size()-1,0) = 1.0f;
            p(keys.size()-1,1) = 0.0f; 
        }
       for (int i = 0; i < keys.size()-2; i++){
           p(i+1,0) = 3.0f*(keys.at(i+2) - keys.at(i)).x;
           p(i+1,1) = 3.0f*(keys.at(i+2) - keys.at(i)).y;
       }

       pPrime = A.inverse() * p;
       for (int i = 0; i < keys.size(); i++) {
           mCtrlPoints.push_back(keys.at(i));
           glm::vec3 prime = glm::vec3(pPrime(i,0), pPrime(i,1), 0.0);
           mCtrlPoints.push_back(prime);
       }
    }

    void setClamped(bool c) { mIsClamped = c; }
    bool isClamped() const { return mIsClamped; }

    void setClampedDirection(const glm::vec3& v) { mClampDir = v; }
    glm::vec3 getClampDirection() const { return mClampDir; }

private:
    bool mIsClamped = true;
    glm::vec3 mClampDir;
};

#endif
