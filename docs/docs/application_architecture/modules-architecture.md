# Modules architecture

Every module contains standalone logic for part of the application.

## Module Directory structure

Module directory located in `Modules\ModuleName`.

Content of `Modules\ModuleName` directory:

```bash
Controller\
Gui\
Logic\
Module\
OrmModel\
Storage\ -- todo
Tasks\
Views\

moduleNameModule.h
moduleNameModule.cpp

moduleNameDefs.h
moduleNameStructs.h
moduleNameTheme.h

#ORM
moduleName.module.xml
moduleName.orm.xml
```

### Controllers

Main access point to module logic. Accessed from Dialogs, MainWindows or other Controllers. Controllers using data from `Views`, calling `Logic` and storing data in `Storage`.

Content of `Modules\ModuleName\Controller` structure:

```bash
Controller\
Controller\iModuleNameController.h
Controller\iModuleNameDataController.h
Controller\moduleNameController.h(cpp)
Controller\moduleNameDataController.h(cpp)
```

### Logic

All logic components of the module.

Content of `Modules\ModuleName\Logic` structure:

```bash
ComponentName\
ComponentName\ComponentPartName\
ComponentName\ComponentPartName\componentPartName.h
ComponentName\ComponentPartName\componentPartName.cpp
ComponentName\componentName.h
ComponentName\componentNameMB.h

moduleNameLogic.pri
```

### Storage

TODO - procistit adresar, procistit tridy

### Views

Logic to create DataPack views from inner components data. Mostly quering and formating logic from datastructures to unified DataPack format.

```bash
Views\
Views\moduleNameView.h
Views\moduleNameView.cpp
Views\moduleNameView.test.cpp
```

## Base modules structure

All shared logic is placed in `Modules\Base` directory.

```bash
Base\Logic

TODO:
- baseModule
- baseMbModule
- base task
- base met task
- base logic component
```

Content of `Modules\Base\Logic` structure:

```bash
Base\Logic\moduleComponentBase.h
Base\Logic\moduleComponentMessageBrokerBridge.h
```


## Component architecture

In module:

Manager -> Is Using MB for accessign data from other modules
  ^
 Logic -> is using IManager to access local and remote data via MB, Logic doesn't use BM, Manager doesn't use remote managers

 but, for example in tradeAnalyzer, in logic, it's better to use ICurrencyManager than calling all MB. it's because we don't need full paralel processing there