/****************************************************************************
 * DisKMonitor, KDE tools to monitor SMART and MDRaid health status         *
 * Copyright (C) 2014-2015 Michaël Lhomme <papylhomme@gmail.com>            *
 *                                                                          *
 * This program is free software; you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation; either version 2 of the License, or        *
 * (at your option) any later version.                                      *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU General Public License along  *
 * with this program; if not, write to the Free Software Foundation, Inc.,  *
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.              *
 ****************************************************************************/



#include "types.h"

#include <KLocalizedString>


/*
 * Constructor
 */
HealthStatus::HealthStatus() : QObject()
{

}



/*
 * Destructor
 */
HealthStatus::~HealthStatus()
{

}



/*
 * Get the current health status value
 */
HealthStatus::Status HealthStatus::getStatus() const
{
  return status;
}



/*
 * Update the status only if the new value is greater than the old one
 */
bool HealthStatus::updateIfGreater(HealthStatus::Status newStatus)
{
  if(newStatus > status) {
    status = newStatus;
    return true;
  } else
    return false;
}



/*
 * Return a string representation of the given health status
 */
QString HealthStatus::toString(HealthStatus::Status status)
{
  switch(status) {
    case Failing: return i18nc("Failing health status", "Failing"); break;
    case Warning: return i18nc("Warning health status", "Warning"); break;
    case Healthy: return i18nc("Healthy health status", "Healthy"); break;
    default: return i18nc("Unknown health status", "Unknown"); break;
  }
}



/*
 *
 */
HealthStatus& HealthStatus::operator =(const HealthStatus::Status& newStatus)
{
  this -> status = newStatus;
  return *this;
}



/*
 *
 */
bool HealthStatus::operator <(const HealthStatus::Status& status)
{
  return this -> status < status;
}
