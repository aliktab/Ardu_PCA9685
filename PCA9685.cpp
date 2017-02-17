/*
  Copyright (C) 2014 Alik <aliktab@gmail.com> All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <I2C.h>
#include <PCA9685.h>


#define PCA9685_CHANNELS_QTY  (uint8_t)16

#define PCA9685_MODE_1        (uint8_t)0x00
#define PCA9685_MODE_2        (uint8_t)0x01

#define PCA9685_SUBADR_1      (uint8_t)0x02
#define PCA9685_SUBADR_2      (uint8_t)0x03
#define PCA9685_SUBADR_3      (uint8_t)0x04

#define PCA9685_PRESCALE      (uint8_t)0xfe

#define PCA9685_LED0_ON_L     (uint8_t)0x06
#define PCA9685_LED0_ON_H     (uint8_t)0x07
#define PCA9685_LED0_OFF_L    (uint8_t)0x08
#define PCA9685_LED0_OFF_H    (uint8_t)0x09

#define PCA9685_ALLLED_ON_L   (uint8_t)0xfa
#define PCA9685_ALLLED_ON_H   (uint8_t)0xfb
#define PCA9685_ALLLED_OFF_L  (uint8_t)0xfc
#define PCA9685_ALLLED_OFF_H  (uint8_t)0xfd

#define PCA9685_MD1_RESTART   (uint8_t)0x80
#define PCA9685_MD1_EXTCLK    (uint8_t)0x40
#define PCA9685_MD1_AI        (uint8_t)0x20
#define PCA9685_MD1_SLEEP     (uint8_t)0x10
#define PCA9685_MD1_ALLCALL   (uint8_t)0x01

#define PCA9685_WAKEUP_PAUSE  (uint8_t)750

#define PCA9685_MAX_TIME      (uint8_t)4095


extern I2C I2c;


PCA9685::PCA9685(uint8_t _i2c_addr)
{
  m_i2c_addr = _i2c_addr;
}

bool PCA9685::initialize(uint8_t _mode, float _freq)
{
  const uint8_t prescale = floor(25000000.0 / (4096.0 * _freq) - 0.5);

  if (I2c.write(m_i2c_addr, PCA9685_MODE_1, (uint8_t)0x0))
    return false;

  I2c.write(m_i2c_addr, PCA9685_MODE_1, PCA9685_MD1_SLEEP);
  I2c.write(m_i2c_addr, PCA9685_PRESCALE, prescale);
  I2c.write(m_i2c_addr, PCA9685_MODE_1, (uint8_t)0x0);
  delay(PCA9685_WAKEUP_PAUSE);

  I2c.write(m_i2c_addr, PCA9685_MODE_1, (uint8_t)(PCA9685_MD1_RESTART | PCA9685_MD1_AI | PCA9685_MD1_ALLCALL));
  I2c.write(m_i2c_addr, PCA9685_MODE_2, _mode);

  return true;
}

uint8_t PCA9685::get_channels_qty() const
{
  return PCA9685_CHANNELS_QTY;
}

void PCA9685::set_on_off(uint8_t _channel, uint16_t _t_on, uint16_t _t_off)
{
  uint8_t Data[4] =
  {
    (_t_on  &  0xff), (_t_on  >> 8) & 0xff,
    (_t_off &  0xff), (_t_off >> 8) & 0xff
  };

  I2c.write(m_i2c_addr, (uint8_t)(PCA9685_LED0_ON_L + 4 * _channel), Data, sizeof(Data));
}

void PCA9685::set_PWM_8(uint8_t _channel, uint8_t _duty_cycle)
{
  set_on_off(
      _channel,
      0,
      (uint16_t)(((uint32_t)_duty_cycle * (uint32_t)PCA9685_MAX_TIME) / (uint32_t)UCHAR_MAX)
    );
}

void PCA9685::set_PWM_16(uint8_t _channel, uint16_t _duty_cycle)
{
  set_on_off(
      _channel,
      0,
      (uint16_t)(((uint32_t)_duty_cycle * (uint32_t)PCA9685_MAX_TIME) / (uint32_t)USHRT_MAX)
    );
}
