# 🌐 HSLCRB VCPKG Registry

![Rasberrysoup Banner](rasberrysoup_banner.png)

> **High-Performance C++ Package Management for Modern Engineering**

Welcome to the official **hslcrb-s_pkgs** registry. This is a centralized vcpkg registry managed by **Rheehose (Rhee Creative)** to host and distribute various C++ libraries, including the **Rasberrysoup** mathematics suite.

---

## 📦 Available Packages

This registry is designed to house multiple packages. Currently, we support:

| Package Name | Version | Description |
| :--- | :--- | :--- |
| `rasberrysoup` | `v1.0.0` | Simplified complex math formulas using keyword calls. |

*More packages (network-lib, ui-lib, etc.) are planned for future releases.*

---

## 🚀 Getting Started

To use packages from this registry, you need to configure your `vcpkg-configuration.json` file in your project root.

### 1. Configure Registry
Add this repository to your `registries` array:

```json
{
  "registries": [
    {
      "kind": "git",
      "repository": "https://github.com/hslcrb/vcpkg_hslcrb-s_pkgs",
      "packages": [ "rasberrysoup" ]
    }
  ]
}
```

### 2. Install Package
Run the following command in your terminal:

```bash
vcpkg install rasberrysoup
```

---

## 📂 Repository Structure

This repository follows the official vcpkg git registry layout:

- `/ports`: Contains the portfiles and configuration for each package.
- `/versions`: Contains the version database for binary compatibility and versioning.
- `README.md`: Registry overview and usage guide.
- `CONTRIBUTING.md`: Instructions for adding new packages.

---

## 🏛 Metadata
- **Creator:** Rheehose (Rhee Creative)
- **Copyright:** © 2008-2026 Rheehose. All rights reserved.
- **Last Updated:** 2026-01-15
- **License:** [MIT](LICENSE)

---

## 🤝 Support
For issues with specific packages or to request new additions, please open an Issue in this repository.
