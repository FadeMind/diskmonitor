#include "drivepropertiesmodel.h"

#include <QFont>
#include <QBrush>
#include <QColor>

#include "humanize.h"


/*
 * Constructor
 */
DrivePropertiesModel::DrivePropertiesModel()
{
  headerLabels << "Id" << "Name" << "Flags" << "Value" << "Worst" << "Threshold" << "Pretty";
  sensitiveAttributes << 1 << 5 << 7 << 196 << 197 << 198;
}



/*
 * Destructor
 */
DrivePropertiesModel::~DrivePropertiesModel()
{

}



/*
 * Retrieve the Drive associated to the model. Can be NULL
 */
Drive* DrivePropertiesModel::getDrive() const
{
  return (Drive*) this -> unit;
}



/*
 * Handler when StorageUnitPropertiesModel refresh the underlying unit
 */
void DrivePropertiesModel::updateInternalState()
{
  Drive* drive = getDrive();

  if(drive != NULL)
    attributes = drive -> getSMARTAttributes();
  else
    attributes.clear();
}



/*
 * Get the number of rows contained in the model's data
 */
int DrivePropertiesModel::rowCount(const QModelIndex& /*index*/) const
{
  return attributes.size();
}



/*
 * Get the number of column of the model
 */
int DrivePropertiesModel::columnCount(const QModelIndex& /*index*/) const
{
  return headerLabels.size();
}



/*
 * Retrieve data for an item in the model
 */
QVariant DrivePropertiesModel::data(const QModelIndex& index, int role) const
{
  if(!index.isValid() || unit == NULL)
    return QVariant();

  SmartAttribute attr = attributes.at(index.row());

  if(role == Qt::BackgroundRole) {
    //set the row background to red if value < threshold
    if(attr.value <= attr.threshold) {
      QBrush brush(QColor("red"));
      return QVariant(brush);

    //set the row background to orange if value is non 0 for sensitive attributes
    } else if(attr.pretty != 0 && sensitiveAttributes.contains(attr.id)) {
      QBrush brush(QColor("orange"));
      return QVariant(brush);

    } else {
      return QVariant();
    }
  }


  if(role == Qt::DisplayRole) {
    switch(index.column()) {
    case 0: return QVariant(attr.id); break;
    case 1: return QVariant(attr.name); break;
    case 2: return QVariant(attr.flags); break;
    case 3: return QVariant(attr.value); break;
    case 4: return QVariant(attr.worst); break;
    case 5: return QVariant(attr.threshold); break;
    case 6: return humanizeSmartAttribute(attr); break;
    case 7: return QVariant(attr.pretty_unit); break;
    default: return QVariant(); break;
    }
  }

  if(index.column() == 6 && role == Qt::ToolTipRole)
    return QVariant(tr("Raw value:") + " " + QString::number(attr.pretty));

  return QVariant();
}



/*
 * Format the 'pretty' value for human readability
 */
QVariant DrivePropertiesModel::humanizeSmartAttribute(const SmartAttribute& attr) const
{
  switch(attr.pretty_unit) {
    case 0: return QVariant(tr("unknown")); break;
    case 1: return QVariant(attr.pretty); break;
    case 2: return QVariant(Humanize::duration(attr.pretty, "ms")); break;
    case 3: return QVariant(QString::number(attr.pretty) + " " + tr("sectors")); break;
    case 4: return QVariant(Humanize::temperature(attr.pretty)); break;
    default: return QVariant();
  }
}




/*
 * Handle the headers of the model
 */
QVariant DrivePropertiesModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if(orientation != Qt::Horizontal)
    return QVariant();

  if(role == Qt::DisplayRole) {
      return QVariant(headerLabels.at(section));

  } else if(role == Qt::FontRole) {
    QFont font;
    font.setBold(true);
    return QVariant(font);
  }

  return QVariant();
}

