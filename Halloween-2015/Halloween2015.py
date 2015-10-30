import pigpio
import time

class Halloween2015:
    """A class controlling Halloween 2015 scary monster"""

    time_step = 1.0 / 25

    def __init__(self, motion_pin, light_r_pin, light_g_pin, light_b_pin, servo_pin, eyes_pin):
        self.motion_pin = motion_pin
        self.light_r_pin = light_r_pin
        self.light_g_pin = light_g_pin
        self.light_b_pin = light_b_pin
        self.servo_pin = servo_pin
        self.eyes_pin = eyes_pin

        self.pi = pigpio.pi()
        self.pi.set_mode(self.motion_pin, pigpio.INPUT)
        self.pi.set_mode(self.light_r_pin, pigpio.OUTPUT)
        self.pi.set_mode(self.light_g_pin, pigpio.OUTPUT)
        self.pi.set_mode(self.light_b_pin, pigpio.OUTPUT)
        self.pi.set_mode(self.servo_pin, pigpio.OUTPUT)
        self.pi.set_mode(self.eyes_pin, pigpio.OUTPUT)

        self.idle = True
        self.cycle_start_time = time.time()

    def run(self):
        while True:
            cycle_time = time.time() - self.cycle_start_time
            if self.idle:
                self.run_idle_cycle(cycle_time)
            else:
                self.run_animation_cycle(cycle_time)
            time.sleep(self.time_step)
        
    def stop(self):
        self.pi.stop()

    def start_idle_cycle(self):
        print "Start idle cycle"
        self.idle = True
        self.cycle_start_time = time.time()

    def run_idle_cycle(self, cycle_time):
        # TODO animate
        self.pi.set_PWM_dutycycle(self.light_r_pin, 255)
        self.pi.set_PWM_dutycycle(self.light_g_pin, 48)
        self.pi.set_PWM_dutycycle(self.light_b_pin, 0)
        self.pi.set_PWM_dutycycle(self.eyes_pin, 0)
        if self.pi.read(self.motion_pin) == 1:
            self.start_animation_cycle()

    def start_animation_cycle(self):
        print "Start ani cycle"
        self.idle = False
        self.cycle_start_time = time.time()

    def run_animation_cycle(self, cycle_time):
        # TODO animate
        self.pi.set_PWM_dutycycle(self.light_r_pin, 0)
        self.pi.set_PWM_dutycycle(self.light_g_pin, 128)
        self.pi.set_PWM_dutycycle(self.light_b_pin, 192)
        self.pi.set_PWM_dutycycle(self.eyes_pin, 255)
        if cycle_time > 20:
            self.start_idle_cycle()


if __name__ == '__main__':
    Halloween2015(motion_pin = 18, light_r_pin = 2, light_b_pin = 4, light_g_pin = 3, eyes_pin = 17,
                  servo_pin = 22).run()