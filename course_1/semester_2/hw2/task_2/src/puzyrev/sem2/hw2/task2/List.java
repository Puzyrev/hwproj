package puzyrev.sem2.hw2.task2;

/**
 * Interface for List class.
 */
public interface List {
    /**
     * Add element to list.
     *
     * @param value element value
     */
    void addValue(int value);

    /**
     * Delete element from list.
     *
     * @param value element value
     */
    void deleteValue(int value);

    /**
     * Check if list is empty.
     *
     * @return 'true' or 'false' if list empty or not
     */
    boolean isEmpty();

    /**
     * Print all list elements.
     */
    void print();
}