# 🛠 Contributing to the Registry

This document outlines the process for adding new C++ packages to the **HSLCRB VCPKG Registry**. By centralizing our libraries here, we ensure efficient dependency management and easy distribution.

---

## 🏗 How to Add a New Package

Follow these steps to deploy a new library to this registry:

### 1. Create the Port Directory
Under the `ports/` directory, create a new folder with your library's name (e.g., `network-lib`).

```bash
mkdir -p ports/my-new-lib
```

### 2. Define `vcpkg.json`
Create a `vcpkg.json` file inside the new port directory. This defines the library's name, version, and dependencies.

```json
{
  "name": "my-new-lib",
  "version": "1.0.0",
  "description": "Short description of the library",
  "maintainer": "Rheehose (Rhee Creative)",
  "license": "MIT"
}
```

### 3. Implement `portfile.cmake`
Create a `portfile.cmake` to tell vcpkg how to download and build the library. Ideally, your source code should be in a separate GitHub repository.

```cmake
vcpkg_from_github(
    OUT_SOURCE_PATH SOURCE_PATH
    REPO hslcrb/my-new-lib
    REF v1.0.0
    SHA512 <HASH_HERE>
)

vcpkg_cmake_configure(SOURCE_PATH "${SOURCE_PATH}")
vcpkg_cmake_install()
vcpkg_cmake_config_fixup()
```

### 4. Update the Versions Database
To make the package discoverable, you must update the `versions/` folder.
- Use `vcpkg x-add-version <portname>` if you have vcpkg installed locally.
- Alternatively, manually update `versions/baseline.json` and create the appropriate letter folder (e.g., `versions/m-/my-new-lib.json`).

### 5. Commit and Push
```bash
git add .
git commit -m "Add new package: my-new-lib"
git push origin main
```

---

## 📝 Best Practices

- **Naming:** Use lowercase, hyphenated names (e.g., `math-lib`, not `MathLib`).
- **Versioning:** Follow Semantic Versioning (v1.0.0).
- **Documentation:** Ensure your library's source repository has a clear README.
- **Header-only:** If it's a header-only library, mark it as `INTERFACE` in CMake.

---

## 📜 Legal
By contributing to this registry, you agree that your contribution is licensed under the same [MIT License](LICENSE) as this repository, unless otherwise specified.

**Creator:** Rheehose (Rhee Creative)
**Years:** 2008-2026
