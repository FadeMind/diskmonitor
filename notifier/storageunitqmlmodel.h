#ifndef STORAGEUNITQMLMODEL_H
#define STORAGEUNITQMLMODEL_H

#include <QAbstractListModel>
#include <QTimer>

#include "storageunit.h"



/*
 * Main model class for the plasma applet
 *
 * Provide a Qt Model to display the Storage units, and
 * global health status
 */
class StorageUnitQmlModel : public QAbstractListModel
{
  Q_OBJECT
  Q_PROPERTY(bool failing READ failing)
  Q_PROPERTY(QString status READ status NOTIFY statusChanged)
  Q_PROPERTY(int refreshTimeout READ refreshTimeout WRITE setRefreshTimeout NOTIFY refreshTimeoutChanged)
  Q_PROPERTY(bool notifyEnabled READ notifyEnabled WRITE setNotifyEnabled)
  Q_PROPERTY(QString iconHealthy READ iconHealthy WRITE setIconHealthy)
  Q_PROPERTY(QString iconFailing READ iconFailing WRITE setIconFailing)

public:
  enum AnimalRoles {
    NameRole = Qt::UserRole + 1,
    DeviceRole,
    FailingRole,
    FailingKnownRole,
    PathRole,
    IconRole
  };

  StorageUnitQmlModel();
  ~StorageUnitQmlModel();

  bool failing() const;
  QString status() const;

  int refreshTimeout() const;
  void setRefreshTimeout(int timeout);

  bool notifyEnabled() const;
  void setNotifyEnabled(bool notify);

  QString iconHealthy() const;
  QString iconFailing() const;
  void setIconHealthy(QString healthyIcon);
  void setIconFailing(QString failingIcon);

  virtual QHash<int, QByteArray> roleNames() const;
  int rowCount(const QModelIndex & parent = QModelIndex()) const;
  QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

private:
  QList<StorageUnit*> storageUnits;

  bool hasFailing = false;
  QList<StorageUnit*> failingUnits;

  int timeout = 5;
  QTimer* timer;

  bool notify = false;

  QString healthyIcon;
  QString failingICon;


  void processUnit(StorageUnit* unit);
  void processUnits(const QList<StorageUnit*> & units);
  QString getIconForUnit(StorageUnit* unit) const;

private slots:
  void storageUnitAdded(StorageUnit* drive);
  void storageUnitRemoved(StorageUnit* path);
  void monitor();

signals:
  void statusChanged();
  void refreshTimeoutChanged(int timeout);

public slots:
  void refresh();
  void openApp(const QString& unitPath = QString());
};

#endif // STORAGEUNITQMLMODEL_H
