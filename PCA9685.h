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

#ifndef __PCA9685__
#define __PCA9685__

#include <inttypes.h>
#include <limits.h>

#define PCA9685_MD2_NONE      (uint8_t)0x00
#define PCA9685_MD2_INVRT     (uint8_t)0x10
#define PCA9685_MD2_OCH       (uint8_t)0x08
#define PCA9685_MD2_OUTDRV    (uint8_t)0x04

class PCA9685
{
public:

  // Create PCA9685 object and link it with specified I2C address.
  PCA9685(uint8_t _i2c_addr);

  // Initialize PCA9685 with second mode (PCA9685_MD2_) and PWM frequency.
  bool initialize(uint8_t _mode, float _freq);

  // Returns channels quantity, supported by the board.
  uint8_t get_channels_qty() const;

  // Set ON and OFF time for specified channel.
  void set_on_off(uint8_t _channel, uint16_t _t_on, uint16_t _t_off);

  // Set PWM duty cycle in range of uint8 for specified channel.
  void set_PWM_8(uint8_t _channel, uint8_t _duty_cycle);

  // Set PWM duty cycle in range of uint16 for specified channel.
  void set_PWM_16(uint8_t _channel, uint16_t _duty_cycle);

private:

  uint8_t m_i2c_addr;
};

#endif // __PCA9685__
