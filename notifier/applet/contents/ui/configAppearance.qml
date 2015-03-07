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


import QtQuick 2.0
import org.kde.plasma.core 2.0 as PlasmaCore
import org.kde.plasma.components 2.0 as PlasmaComponents
import QtQuick.Controls 1.0 as QtControls
import QtQuick.Layouts 1.1
import org.papylhomme.diskmonitor 0.1 as DiskMonitor


Item {
  id: appearancePage
  anchors.fill: parent

  property alias cfg_includeDriveId: includeDriveId.checked
  property alias cfg_smallDeviceName: smallDeviceName.checked
  property alias cfg_layoutBig: layoutBig.checked
  property alias cfg_layoutSmall: layoutSmall.checked
  property alias cfg_layoutMinimalist: layoutMinimalist.checked

  property alias cfg_iconsFaces: iconsFaces.checked
  property alias cfg_iconsDialog: iconsDialog.checked
  property alias cfg_iconsCustom: iconsCustom.checked
  property alias cfg_iconHealthy: iconHealthy.icon
  property alias cfg_iconFailing: iconFailing.icon
  property alias cfg_iconWarning: iconWarning.icon
  property alias cfg_iconUnknown: iconUnknown.icon

  property alias cfg_warningColor: warningColor.color
  property alias cfg_errorColor: errorColor.color

  IconsProvider {
    id: iconsProvider
  }


  ColumnLayout {
    anchors.left: parent.left
    anchors.right: parent.right

    /*
     * Layout configurations
     */
    QtControls.GroupBox {
      Layout.fillWidth: true
      title: i18n("Layouts")

      ColumnLayout {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.topMargin: 10

        QtControls.CheckBox {
          id: smallDeviceName
          text: i18n("Use small device name")
        }

        QtControls.CheckBox {
          id: includeDriveId
          text: i18n("Include drive id on small layouts")
        }

        QtControls.ExclusiveGroup { id: layoutType }

        GridLayout {
          columns: 2
          columnSpacing: 10
          rowSpacing: 10


          //big layout
          QtControls.RadioButton {
            id: layoutBig
            text: i18nc("Big layout", "Big")
            exclusiveGroup: layoutType
          }
  
          StorageUnitBig {
            id: unitBig
            Layout.fillWidth: true
            property string icon: "drive-harddisk"
            property var healthStatus: DiskMonitor.HealthStatus.Healthy
            property string name: "Drive_ID"
            property string device: "/dev/sdX"
          }


          //small layout
          QtControls.RadioButton {
            id: layoutSmall
            text: i18nc("Small layout", "Small")
            exclusiveGroup: layoutType
          }

          StorageUnitSmall {
            id: unitSmall
            Layout.fillWidth: true
            property string icon: "drive-harddisk"
            property var healthStatus: DiskMonitor.HealthStatus.Healthy
            property string name: "Drive_ID"
            property string device: "/dev/sdX"
          }


          //minimalist layout 
          QtControls.RadioButton {
            id: layoutMinimalist
            text: i18nc("Minimalist layout", "Minimalist")
            exclusiveGroup: layoutType
          }

          StorageUnitMinimalist {
            id: unitMinimalist
            Layout.fillWidth: true
            property string icon: "drive-harddisk"
            property var healthStatus: DiskMonitor.HealthStatus.Healthy
            property string name: "Drive_ID"
            property string device: "/dev/sdX"
          }
        }
      }
    }


    /*
     * Icons configuration
     */
    QtControls.GroupBox {
      Layout.fillWidth: true
      title: i18n("Icons")

      QtControls.ExclusiveGroup { id: iconType }

      GridLayout {
        columns: 5
        columnSpacing: 10
        rowSpacing: 10
        anchors.top: parent.top
        anchors.topMargin: 10


        //faces icons
        QtControls.RadioButton {
          id: iconsFaces
          text: i18nc("Emote icons", "Emotes")
          exclusiveGroup: iconType
        }

        PlasmaCore.IconItem {
          source: "face-cool"
        }
        PlasmaCore.IconItem {
          source: "face-sick"
        }
        PlasmaCore.IconItem {
          source: "face-angry"
        }
        PlasmaCore.IconItem {
          source: "face-confused"
        }


        //dialog icons
        QtControls.RadioButton {
          id: iconsDialog
          text: i18nc("Dialog icons", "Dialogs")
          exclusiveGroup: iconType
        }

        PlasmaCore.IconItem {
          source: "dialog-ok"
        }
        PlasmaCore.IconItem {
          source: "dialog-error"
        }
        PlasmaCore.IconItem {
          source: "dialog-warning"
        }
        PlasmaCore.IconItem {
          source: "unknown"
        }

        //custom icons
        QtControls.RadioButton {
          id: iconsCustom
          text: i18nc("Custom icons", "Custom")
          exclusiveGroup: iconType
        }

        IconPickerButton {
          id: iconHealthy
        }
        IconPickerButton {
          id: iconFailing
        }
        IconPickerButton {
          id: iconWarning
        }
        IconPickerButton {
          id: iconUnknown
        }
      }
    }


    /*
     * Colors configuration
     */
    QtControls.GroupBox {
      Layout.fillWidth: true
      title: i18n("Colors")

      GridLayout {
        columns: 2
        columnSpacing: 10
        anchors.top: parent.top
        anchors.topMargin: 10

        //warning color
        PlasmaComponents.Label {
          text: i18nc("Warning color", "Warning")
        }

        ColorPickerButton {
          id: warningColor
          color: "orange"
        }

        //error color
        PlasmaComponents.Label {
          text: i18nc("Error color", "Error")
        }

        ColorPickerButton {
          id: errorColor
          color: "red"
        }
      }
    }
  }

  Component.onCompleted: {
    includeDriveId.checked = plasmoid.configuration.includeDriveId;
    smallDeviceName.checked = plasmoid.configuration.smallDeviceName;

    warningColor.color = plasmoid.configuration.warningColor;
    errorColor.color = plasmoid.configuration.errorColor;

    iconHealthy.icon = plasmoid.configuration.iconHealthy;
    iconFailing.icon = plasmoid.configuration.iconFailing;
    iconWarning.icon = plasmoid.configuration.iconWarning;
    iconUnknown.icon = plasmoid.configuration.iconUnknown;

    if(plasmoid.configuration.layoutBig) {
        layoutBig.checked = true;
    } else if(plasmoid.configuration.layoutSmall) {
        layoutSmall.checked = true;
    } else {
        layoutMinimalist.checked = true;
    }

    if(plasmoid.configuration.iconsFaces) {
        iconsFaces.checked = true;
    } else if(plasmoid.configuration.iconsDialog) {
        iconsDialog.checked = true;
    } else {
        iconsCustom.checked = true;
    }

    unitBig.healthStatus = DiskMonitor.HealthStatus.Healthy;
    unitSmall.healthStatus = DiskMonitor.HealthStatus.Healthy;
    unitMinimalist.healthStatus = DiskMonitor.HealthStatus.Healthy;
  }

}
