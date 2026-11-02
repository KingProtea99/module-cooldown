# Cooldowns (MealKit module)

Tick-based cooldowns for [MealKit](https://github.com/MealKit-Engine/MealKit) games, with a fill bar `.ui` component. Docs: [docs/index.md](docs/index.md).

> **Beta (v0.x).** MealKit is under active development: APIs and file formats may change between versions until v1.0, and projects are moved forward with the upgrade tool. Feedback and bug reports are welcome.

```
tools\module.ps1 add -Project <your project> cooldown
```

Tests (not copied into projects): `cmake -S tests -B build/tests -G Ninja -DMEALKIT_ROOT=<engine> -DMEALKIT_HEADLESS_ONLY=ON`, then build and run `cooldown_tests`.

MIT license.
