--Waterspray particle effect
-- Author: Bertram

systems = {}

systems[0] =
{
    enabled = true,

    emitter =
    {
        x = 0,
        y = -64,
        x2 = 0, --useless when using a circle shape
        y2 = 0, --useless when using a circle shape
        center_x = 0,  --useless when using a circle shape
        center_y = 0,  --useless when using a circle shape
        x_variation = 0,
        y_variation = 0,
        radius = 80,
        shape = 'circle',
        omnidirectional = false,
        orientation = -1.6, --up
        angle_variation = 0.0,
        initial_speed = 10,
        initial_speed_variation = 15,
        emission_rate = 1,
        start_time = 0,
        emitter_mode = 'burst',
        spin = 'counter clockwise'
    },

    keyframes =
    {
        {  -- keyframe 1
            size_x = 0.6,
            size_y = 0.6,
            color={0.0, 0.0, 1.0, 0.6},
            rotation_speed = -30.0,
            size_variation_x = 0.2,
            size_variation_y = 0.2,
            rotation_speed_variation = 0.0,
            color_variation = {0.0, 0.0, 0.0, 0.0},
            time = 0.0
        },

        {  -- keyframe 2
            size_x = 0.3,
            size_y = 0.3,
            color = {0.5, 0.5, 1.0, 0.4},
            rotation_speed = -30.0,
            size_variation_x = 0.2,
            size_variation_y = 0.2,
            rotation_speed_variation = 0.0,
            color_variation = {0.0, 0.0, 0.0, 0.0},
            time = 1.0
        }

    },

    animation_frames =
    {
        'data/visuals/particle_effects/wave.png'
    },
    animation_frame_times =
    {
        16
    },

    blend_mode = 13,
    system_lifetime = 0.3,
    particle_lifetime = 0.5,
    particle_lifetime_variation = 0.0,
    max_particles = 1,
    damping = 1,
    damping_variation = 0,
    acceleration_x = 0,
    acceleration_y = 0,
    acceleration_variation_x = 0,
    acceleration_variation_y = 0,
    wind_velocity_x = 0,
    wind_velocity_y = 0,
    wind_velocity_variation_x = 0,
    wind_velocity_variation_y = 0,

    tangential_acceleration = 300,
    tangential_acceleration_variation = 0,
    radial_acceleration = 0,
    radial_acceleration_variation = 0,
    user_defined_attractor = false,
    attractor_falloff = 0.0,

    smooth_animation = true,
    modify_stencil = false,
    stencil_op = 'INCR',
    use_stencil = false,
    random_initial_angle = true
}
