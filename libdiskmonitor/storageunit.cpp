#include "storageunit.h"

#include <QDebug>



/*
 * Initialize a new StorageUnit
 *
 * @param objectPath The DBus object path to the UDisks2 node represented by this unit
 * @param device A string identifying the underlying Linux device (/dev/sdX, /dev/mdX)
 */
StorageUnit::StorageUnit(QDBusObjectPath objectPath, QString device) : QObject()
{
  this -> objectPath = objectPath;
  this -> device = device;
  this -> name = objectPath.path().split("/").last();
  this -> shortName = name;
}



/*
 * Empty constructor, required by QMETA_TYPE, DO NOT USE !
 */
StorageUnit::StorageUnit() : QObject()
{
  qCritical() << "Should not be called ! Only required by QMETA_TYPE (TODO: do something about it ?)";
}



/*
 * Copy constructor, required by QMETA_TYPE
 *
 * @param other The unit to copy
 */
StorageUnit::StorageUnit(const StorageUnit& other) : QObject()
{
  this -> objectPath = other.objectPath;
  this -> device = other.device;
  this -> name = other.objectPath.path().split("/").last();
}




/*
 * Destructor
 */
StorageUnit::~StorageUnit()
{

}



/*
 * Get the DBus path to the UDisks2 node represented by this StorageUnit
 */
QDBusObjectPath StorageUnit::getObjectPath() const
{
  return this -> objectPath;
}



/*
 * Get a string representation of the DBus path
 *
 * @see StorageUnit::getObjectPath()
 */
QString StorageUnit::getPath() const
{
  return this -> objectPath.path();
}



/*
 * Get a string identifying the underlying Linux device (/dev/sdX, /dev/mdX)
 */
QString StorageUnit::getDevice() const
{
  return this -> device;
}



/*
 * Get the StorageUnit's name. Depend on the type of unit
 */
QString StorageUnit::getName() const
{
  return this -> name;
}



/*
 * Get the StorageUnit's short name. Depend on the type of unit
 */
QString StorageUnit::getShortName() const
{
  return this -> shortName;
}



/*
 * Test if this unit is considered failing
 */
bool StorageUnit::isFailing() const
{
  return this -> failing;
}



/*
 * Test if the failing status of the unit is known
 */
bool StorageUnit::isFailingStatusKnown() const
{
  return this -> failingStatusKnown;
}



/*
 * Retrieve a property on the UDisks2 node identified by name
 *
 * @param iface The DBus interface containing the property
 * @param name The name of the property to retrieve
 */
QVariant StorageUnit::getProperty(QDBusInterface* iface, const char* name) const
{
  QVariant prop = iface -> property(name);
  if(!prop.isValid())
    qCritical() << "Unable to read property '" << name <<
                "' from interface '" << iface -> interface() << "': " <<
                iface -> lastError();

  return prop;
}



/*
 * Convenience wrapper around StorageUnit::getProperty() for bool type (DBus type 'b')
 */
bool StorageUnit::getBoolProperty(QDBusInterface* iface, const char* name) const
{
  return getProperty(iface, name).toBool();
}



/*
 * Convenience wrapper around StorageUnit::getProperty() for int type (DBus type 'i')
 */
int StorageUnit::getIntProperty(QDBusInterface* iface, const char* name) const
{
  return getProperty(iface, name).toInt();
}



/*
 * Convenience wrapper around StorageUnit::getProperty() for int ulonglong (DBus type 't')
 */
qulonglong StorageUnit::getULongLongProperty(QDBusInterface* iface, const char* name) const
{
  return getProperty(iface, name).toULongLong();
}



/*
 * Convenience wrapper around StorageUnit::getProperty() for double type (DBus type 'd')
 */
double StorageUnit::getDoubleProperty(QDBusInterface* iface, const char* name) const
{
  return getProperty(iface, name).toDouble();
}



/*
 * Convenience wrapper around StorageUnit::getProperty() for string type (DBus type 's')
 */
QString StorageUnit::getStringProperty(QDBusInterface* iface, const char* name) const
{
  return getProperty(iface, name).toString();
}




