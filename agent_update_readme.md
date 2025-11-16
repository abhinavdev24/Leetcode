# README Problem Table Update Agent

Use this document whenever the Problems table in `README.md` needs to be regenerated.

## Inputs

- `problems.csv` – authoritative list of problems with IDs, slugs, difficulty level, topics, and canonical URLs.

## Steps

1. From the repository root, run the helper snippet to build the Markdown table sorted by numeric ID. The slug column should render as a hyperlink to each problem’s `Readme.md`.

   ```bash
   python - <<'PY'
   import csv

   rows = []
   with open('problems.csv', newline='') as f:
       for row in csv.DictReader(f):
           rows.append((
               int(row['id']),
               row['slug'],
               row['difficulty'],
               row['topics'].replace(';', ', '),
               row['url'],
           ))

   rows.sort()
   print('| id | slug | difficulty | topics | url |')
   print('| --- | --- | --- | --- | --- |')
   for pid, slug, difficulty, topics, url in rows:
       link = f'[{slug}](problems/{pid}_{slug}/Readme.md)'
       print(f'| {pid} | {link} | {difficulty} | {topics} | {url} |')
   PY
   ```

2. Copy the resulting table output into the `## Problems` section in `README.md`, replacing the previous table under that heading.
3. Ensure the short lead-in sentence under `## Problems` still states that the table is generated from `problems.csv`.
4. Save the file and review the diff to confirm every row includes the correct hyperlink, difficulty, topics, and URL values pulled from `problems.csv`.

The README section is now synchronized with `problems.csv`.
