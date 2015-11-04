import math
import pigpio
import time
import sys
import os

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
        try:
            while True:
                cycle_time = time.time() - self.cycle_start_time
                if self.idle:
                    self.run_idle_cycle(cycle_time)
                else:
                    self.run_animation_cycle(cycle_time)
                time.sleep(self.time_step)
        except KeyboardInterrupt:
            print "Interrupted"
        
    def stop(self):
        self.pi.set_PWM_dutycycle(self.light_r_pin, 0)
        self.pi.set_PWM_dutycycle(self.light_g_pin, 0)
        self.pi.set_PWM_dutycycle(self.light_b_pin, 0)
        self.pi.set_PWM_dutycycle(self.eyes_pin, 0)
        self.pi.set_servo_pulsewidth(self.motion_pin, 0)
        self.pi.stop()

    def start_idle_cycle(self):
        print "Start idle cycle"
        self.idle = True
        self.cycle_start_time = time.time()

    def run_idle_cycle(self, cycle_time):
        self.pi.set_PWM_dutycycle(self.light_r_pin, 255)
        g = self.animate_sin(0, 48, 1, time.time())
        self.pi.set_PWM_dutycycle(self.light_g_pin, g)
        self.pi.set_PWM_dutycycle(self.light_b_pin, 0)
        self.pi.set_PWM_dutycycle(self.eyes_pin, 0)
        self.pi.set_servo_pulsewidth(self.servo_pin, 0)

        if cycle_time > 14 and self.pi.read(self.motion_pin) == 1:
            self.start_animation_cycle()

    def start_animation_cycle(self):
        print "%s: Start ani cycle" % time.strftime("%H:%M:%S")
        self.idle = False
        self.cycle_start_time = time.time()
        os.system('mplayer moro.ogg &')

    def run_animation_cycle(self, cycle_time):
        r_base = 255
        r_mix = 0
        r = self.animate_mix(3, 4, 4, 3, r_base, r_mix, cycle_time)
        self.pi.set_PWM_dutycycle(self.light_r_pin, r)
        g_base = self.animate_sin(0, 48, 1, time.time())
        g_mix = self.animate_sin(64, 192, 3, cycle_time)
        g = self.animate_mix(3, 4, 4, 3, g_base, g_mix, cycle_time)
        self.pi.set_PWM_dutycycle(self.light_g_pin, g)
        b_base = 0
        b_mix = 192
        b = self.animate_mix(3, 4, 4, 3, b_base, b_mix, cycle_time)
        self.pi.set_PWM_dutycycle(self.light_b_pin, b)
        eyes_base = 0
        eyes_mix = 255
        eyes = self.animate_mix(6, 1, 5, 1, eyes_base, eyes_mix, cycle_time)
        self.pi.set_PWM_dutycycle(self.eyes_pin, eyes)

        head_start = self.animate_mix(6, 0.15, 0.35, 0.15, 1500, 600, cycle_time)
        head = self.animate_mix(12, 0.25, 0.15, 0.35, head_start, 2400, cycle_time)
        self.pi.set_servo_pulsewidth(self.servo_pin, head)

        if cycle_time > 14:
            self.start_idle_cycle()

    def animate_sin(self, min_value, max_value, period, time):
        return min_value + (max_value - min_value) * 0.5 * (1 + math.sin(time * 2 * 3.1415296 / period))

    def animate_pulse(self, min_value, max_value, period, time):
        return min_value + (max_value - min_value) * math.fabs(math.sin(time * 2 * 3.1415296 / period))

    def animate_mix(self, delay, attack, sustain, decay, base_value, mix_value, time):
        if time < delay:
            return base_value
        time -= delay
        if time < attack:
            return base_value + (mix_value - base_value) * time / attack
        time -= attack
        if time < sustain:
            return mix_value
        time -= sustain
        if time < decay:
            return mix_value + (base_value - mix_value) * time / decay
        else:
            return base_value


if __name__ == '__main__':
    robot = Halloween2015(motion_pin = 18, light_r_pin = 2, light_b_pin = 3, light_g_pin = 4, eyes_pin = 17,
                  servo_pin = 22)
    robot.run()
    robot.stop()
    sys.exit(0)
