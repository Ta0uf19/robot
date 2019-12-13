//
// Created by Taoufik on 12/11/2019.
//

#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H


#include "PID.h"
#include "ICodeurManager.h"
#include "Odometry.h"
#include "MoteurManager.h"
#include "MathUtils.h"
#include "Config.h"


/**
   * Consigne
   */

typedef enum {
    ALPHA_DELTA,
    ALPHA,
    MSTOP,
} Trajectory;

class Controller {

public:
    /**
     * Initialisation de l'asservisement
     * @param codeurs
     * @param motor
     * @param config
    */
    Controller(ICodeurManager& codeurs, MoteurManager& motor, Config& config);
    void update();

    /**
     * @brief Consigne de de déplacement
     * Calcul erreur entre la consigne et la position actuelle du robot
    **/
    void updateConsigne();
    void updateSpeed();
    void rotate();
    /**
     * Déplacement x, y, angle
     * Target Position
     *
     * @param x
     * @param y
     * @param angle
    */
    void gotoPoint(int x, int y, int angle);
    void stop();
    bool positionReached();
    /** enum Direction
	 *  \brief Sens de déplacement pour le robot.
	 */
    enum Direction {
        FORWARD     = 1, ///< Le robot avance en marche avant.
        BACKWARD    = -1 ///< Le robot avance en marche arrière.
    };

    void setTrajectory(Trajectory trajectory) { m_trajectory = trajectory; };

private:
    // PID Controller
    PID m_leftSpeedPID;
    PID m_rightSpeedPID;
    PID m_translationPID;
    PID m_rotationPID;

    // Target position
    Position m_targetPos;

    // Trajectory
    Trajectory m_trajectory;

    /**
     * Structure de la consigne à atteindre
     */
    struct
    {
        float distance = 0.0; // mm
        float angle = 0.0; // rad

    } m_consigne;

    int m_direction = 0;

    float m_maxTranslationSpeed = 0; // mm/s
    float m_maxRotationSpeed = 0; // mm/s
    int m_maxPWM = 0;

    //Odometry
    Odometry m_odometry;

    // MoteurManager
    MoteurManager m_motor;
    //Config
    Config m_config;

};


#endif //ROBOT_CONTROLLER_H
