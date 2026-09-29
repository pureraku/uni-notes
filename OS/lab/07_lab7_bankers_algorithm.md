# Lab 7 — Banker's Algorithm for Deadlock Avoidance

**Priority: 🔴 High**

## 🎯 Core Idea

Banker's Algorithm avoids deadlock by checking whether granting a resource request would leave the system in a **safe state**. Instead of granting every currently possible request, the system evaluates whether all processes can still finish in some order.

## 🧠 Understand It

The key matrices/vectors are:

- **Available:** currently available instances of each resource type.
- **Max:** maximum demand declared by each process.
- **Allocation:** resources currently allocated to each process.
- **Need:** remaining maximum demand.

The central equation is:

$$
Need = Max - Allocation
$$

### Safe-state test

Start with:

$$
Work = Available
$$

and mark all processes unfinished.

Find a process $P_i$ satisfying:

$$
Need_i \le Work
$$

Then conceptually let it finish and release its allocation:

$$
Work = Work + Allocation_i
$$

Repeat until:

- all processes can finish → safe state;
- no unfinished process can satisfy `Need <= Work` → unsafe state.

## 💡 Worked Example

Suppose:

```text
Available = (3, 3, 2)
```

and:

```text
Allocation       Max
P0  (0,1,0)      (7,5,3)
P1  (2,0,0)      (3,2,2)
P2  (3,0,2)      (9,0,2)
P3  (2,1,1)      (2,2,2)
P4  (0,0,2)      (4,3,3)
```

Compute:

```text
Need = Max - Allocation

P0  (7,4,3)
P1  (1,2,2)
P2  (6,0,0)
P3  (0,1,1)
P4  (4,3,1)
```

Now start with:

```text
Work = (3,3,2)
```

`P1` can finish because:

```text
(1,2,2) <= (3,3,2)
```

After it finishes:

```text
Work = (3,3,2) + (2,0,0)
     = (5,3,2)
```

`P3` can now finish:

```text
(0,1,1) <= (5,3,2)
```

so:

```text
Work = (5,3,2) + (2,1,1)
     = (7,4,3)
```

Then `P0` can finish:

```text
(7,4,3) <= (7,4,3)
```

giving:

```text
Work = (7,4,3) + (0,1,0)
     = (7,5,3)
```

Then `P2` can finish, followed by `P4`. Therefore this particular state has a safe completion sequence.

## 📐 Why `Need = Max - Allocation`

For each resource type:

```text
Maximum required
        -
Already allocated
        =
Remaining possible requirement
```

So:

$$
Need_{ij} = Max_{ij} - Allocation_{ij}
$$

This is a reasoning relationship, not merely a formula to memorize.

## 🔗 Connections

```text
Resource allocation
      ↓
Potential deadlock
      ↓
Check future completion possibility
      ↓
Safe / unsafe state
      ↓
Grant or defer request
```

## 📊 Safe vs Unsafe vs Deadlocked

| State | Meaning |
|---|---|
| Safe | There exists an order in which every process can finish |
| Unsafe | No safe completion sequence is found |
| Deadlocked | Processes are actually stuck waiting |

An unsafe state is a warning that deadlock may become possible; it is not synonymous with an already-detected deadlock.

## ⚠️ Common Confusions / Traps

- `Need` is not `Max`; it is remaining demand.
- Compare vectors component-by-component.
- An unsafe state is not automatically a currently deadlocked state.
- A safe sequence is an ordering, not necessarily the actual execution order.
- Releasing a process's allocation changes `Work`.

## 📝 What to Remember

### 🔴 Must Understand
- Safe state concept.
- `Need = Max - Allocation`.
- `Work` update.
- Safe-sequence reasoning.

### 🟡 Must Remember
- Meaning of Available, Max, Allocation, Need.
- Component-wise comparison.

### 🟢 Nice to Know
- Variants of resource-request algorithms.

## ✅ Quick Check

1. Why is `Need = Max - Allocation`?
2. What does `Work` represent?
3. What condition allows a process to be selected in the safety test?
4. Why is the process's allocation added to `Work` after it finishes?
5. Is an unsafe state the same as deadlock?
6. What does a safe sequence prove?
